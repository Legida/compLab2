#include "FuncGraphsProvider.h"

#include <QPainter>

namespace
{
    static constexpr int _imageWidth = 1000;
    static constexpr int _imageHeight = 1000;
}

FuncGraphsProvider::FuncGraphsProvider(QString name, int xSide, int ySide, RFunction func)
    : QQuickImageProvider(QQuickImageProvider::Image)
    , rfunc(func)
    , m_xSide(xSide)
    , m_ySide(ySide)
    , m_name(name)
{
    rect.resize(_imageHeight);
    #pragma omp parallel for
    for (auto& el : rect)
    {
        el.resize(_imageWidth);
    }
    computeRect();
}

FuncGraphsProvider::FuncGraphsProvider(FuncGraphsProvider&& other)
    : QQuickImageProvider(QQuickImageProvider::Image)
    , rect(std::move(other.rect))
    , rfunc(std::move(other.rfunc))
    , m_xSide(std::move(other.m_xSide))
    , m_ySide(std::move(other.m_ySide))
    , m_name(std::move(other.m_name))
{
}

QImage FuncGraphsProvider::requestImage(const QString& id, QSize* size, const QSize& requestedSize)
{
    if (size)
    {
        *size = QSize(_imageWidth, _imageHeight);
    }

    if (id == "MImage")
    {
        return requestMImage();
    }
    else if (id == "x")
    {
        return requestComponent(EComponents::x);
    }
    else if (id == "y")
    {
        return requestComponent(EComponents::y);
    }
    else if (id == "z")
    {
        return requestComponent(EComponents::z);
    }

    return QImage();
}

void FuncGraphsProvider::saveImages(QString str)
{
    const QUrl url(str);
    if (!url.isLocalFile())
    {
        return;
    }
    str = url.toLocalFile();
    requestMImage().save(str + "/" + "MImage.png", "PNG");
    requestComponent(EComponents::x).save(str + "/" + "x.png", "PNG");
    requestComponent(EComponents::y).save(str + "/" + "y.png", "PNG");
    requestComponent(EComponents::z).save(str + "/" + "z.png", "PNG");
}

QImage FuncGraphsProvider::requestMImage()
{
    QImage image(_imageWidth, _imageHeight, QImage::Format_RGB32);

    const QRgb positiveColor = QColor(Qt::white).rgb();
    const QRgb negativeColor = QColor(QColorConstants::Svg::mediumblue).rgb();

    #pragma omp parallel for
    for (int i = 0; i < _imageHeight; ++i)
    {
        QRgb* row = reinterpret_cast<QRgb*>(image.scanLine(i));

        for (int j = 0; j < _imageWidth; ++j)
        {
            rect[j][i].z >= 0.f ? row[j] = positiveColor : row[j] = negativeColor;
        }
    }

    return image;
}

QImage FuncGraphsProvider::requestComponent(EComponents component)
{
    QImage image(_imageWidth, _imageHeight, QImage::Format_RGB32);

    #pragma omp parallel for
    for (int i = 0; i < _imageHeight; ++i)
    {
        QRgb* row = reinterpret_cast<QRgb*>(image.scanLine(i));

        for (int j = 0; j< _imageWidth; ++j)
        {
            const float x1 = static_cast<float>(j-_imageWidth/2)/m_xSide;
            const float y1 = static_cast<float>(i-_imageHeight/2)/m_ySide;
            const float z1 = rect[j][i].z;

            const int j2 = j < (_imageWidth - 1) ? (j + 1) : (j - 1);
            const float x2 = static_cast<float>(j2-_imageWidth/2)/m_xSide;
            const float y2 = static_cast<float>(i-_imageHeight/2)/m_ySide;
            const float z2 = rect[j2][i].z;

            const int i3 = i < (_imageHeight - 1) ? (i + 1) : (i - 1);
            const float x3 = static_cast<float>(j-_imageWidth/2)/m_xSide;
            const float y3 = static_cast<float>(i3-_imageHeight/2)/m_ySide;
            const float z3 = rect[j][i3].z;

            const float A = matrix3Determinant({y1, z1, 1, y2, z2, 1, y3, z3, 1});
            const float B = matrix3Determinant({x1, z1, 1, x2, z2, 1, x3, z3, 1});
            const float C = matrix3Determinant({x1, y1, 1, x2, y2, 1, x3, y3, 1});
            const float D = matrix3Determinant({x1, y1, z1, x2, y2, z2, x3, y3, z3});

            const float l = std::sqrt(A*A + B*B + C*C + D*D);

            float p = 0.f;
            switch (component)
            {
            case EComponents::x:
                p = A/l;
                break;
            case EComponents::y:
                p = B/l;
                break;
            case EComponents::z:
                p = C/l;
                break;
            default:
                break;
            }

            const int c = 128 + 128*p;
            row[j] = QColor(c, c, c).rgb();
        }
    }

    return image;
}

QString FuncGraphsProvider::getName() const
{
    return m_name;
}

void FuncGraphsProvider::computeRect()
{
    #pragma omp parallel for
    for (int i = 0; i < _imageHeight; ++i)
    {
        for (int j = 0; j < _imageWidth; ++j)
        {
            const float x = static_cast<float>(j-_imageWidth/2)/m_xSide;
            const float y = static_cast<float>(i-_imageHeight/2)/m_ySide;

            rect[j][i].z = rfunc(x, y);
        }
    }
}

void FuncGraphsProvider::computeNormals()
{
    #pragma omp parallel for
    for (int i = 0; i < _imageHeight; ++i)
    {
        for (int j = 0; j< _imageWidth; ++j)
        {
            const float x1 = static_cast<float>(j-_imageWidth/2)/m_xSide;
            const float y1 = static_cast<float>(i-_imageHeight/2)/m_ySide;
            const float z1 = rect[j][i].z;

            const int j2 = j < (_imageWidth - 1) ? (j + 1) : (j - 1);
            const float x2 = static_cast<float>(j2-_imageWidth/2)/m_xSide;
            const float y2 = static_cast<float>(i-_imageHeight/2)/m_ySide;
            const float z2 = rect[j2][i].z;

            const int i3 = i < (_imageHeight - 1) ? (i + 1) : (i - 1);
            const float x3 = static_cast<float>(j-_imageWidth/2)/m_xSide;
            const float y3 = static_cast<float>(i3-_imageHeight/2)/m_ySide;
            const float z3 = rect[j][i3].z;

            const float A = matrix3Determinant({y1, z1, 1, y2, z2, 1, y3, z3, 1});
            const float B = matrix3Determinant({x1, z1, 1, x2, z2, 1, x3, z3, 1});
            const float C = matrix3Determinant({x1, y1, 1, x2, y2, 1, x3, y3, 1});
            const float D = matrix3Determinant({x1, y1, z1, x2, y2, z2, x3, y3, z3});

            const float l = std::sqrt(A*A + B*B + C*C + D*D);

            rect[j][i].nx /=l;
            rect[j][i].ny /=l;
            rect[j][i].nz /=l;
        }
    }
}

float FuncGraphsProvider::matrix3Determinant(std::array<std::array<float, 3>, 3> m)
{
    return m[0][0]*matrix2Determinant({m[1][1], m[1][2], m[2][1], m[2][2]})
          -m[0][1]*matrix2Determinant({m[1][0], m[1][2], m[2][0], m[2][2]})
          +m[0][2]*matrix2Determinant({m[1][0], m[1][1], m[2][0], m[2][1]});
}

float FuncGraphsProvider::matrix2Determinant(std::array<std::array<float, 2>, 2> m)
{
    return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}
