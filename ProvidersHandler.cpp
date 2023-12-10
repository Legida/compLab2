#include "ProvidersHandler.h"

#include <QQmlContext>

ProvidersHandler::ProvidersHandler(QQmlApplicationEngine& engine) : m_engine(engine)
{
    m_engine.rootContext()->setContextProperty("handler", this);
}

void ProvidersHandler::addProvider(QPointer<FuncGraphsProvider> provider)
{
    const auto name = provider->getName();
    m_providers.push_back(std::move(provider));
    m_engine.addImageProvider(name, m_providers.back().get());
    Q_EMIT providerCountChanges(m_providers.size());
}

QStringList ProvidersHandler::getProvidersNames()
{
    QStringList list;
    for (auto& pr : m_providers)
    {
        list.push_back(pr->getName());
    }

    return list;
}

void ProvidersHandler::saveImage(const QString& providerName, const QString& path)
{
    auto res = std::find_if(m_providers.begin(), m_providers.end(),
                         [providerName](const QPointer<FuncGraphsProvider>& pr)
    {
        return QString::compare(providerName, pr->getName(), Qt::CaseInsensitive);
    });

    if (res != m_providers.end())
    {
        res->get()->saveImages(path);
    }
}
