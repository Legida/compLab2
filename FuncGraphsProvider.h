#ifndef FUNC_GRAPHS_PROVIDER
#define FUNC_GRAPHS_PROVIDER

#include <QQuickImageProvider>
#include <QSize>

#include <functional>
#include <memory>
#include <vector>

#include "OperatorHelper.h"

class FuncGraphsProvider : public QQuickImageProvider
{
public:
    FuncGraphsProvider(QString name, int xSide, int ySide, RFunction func);
    FuncGraphsProvider(FuncGraphsProvider&& other);

    QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize) override;
    QString getName() const;

    void saveImages(QString str);

private:
    enum class EComponents
    {
        x,
        y,
        z
    };

    QImage requestMImage();
    QImage requestComponent(EComponents component);

    void computeRect();
    void computeNormals();

    float matrix3Determinant(std::array<std::array<float, 3>, 3> matrix);
    float matrix2Determinant(std::array<std::array<float, 2>, 2> matrix);

    const RFunction rfunc;

    struct info
    {
        float z;
        float nx;
        float ny;
        float nz;
    };

    std::vector<std::vector<info>> m_rect;
    const int m_xSide;
    const int m_ySide;
    const QString m_name;
    QString m_rgbColor;
};

#endif //FUNC_GRAPHS_PROVIDER
