#ifndef PROVIDER_HANDLER
#define PROVIDER_HANDLER

#include <QQmlApplicationEngine>
#include <QStringList>
#include <QObject>

#include <list>

#include "FuncGraphsProvider.h"


class ProvidersHandler : public QObject
{
    Q_OBJECT

public:
    ProvidersHandler(QQmlApplicationEngine& engine);

    void addProvider(QPointer<FuncGraphsProvider> provider);

    Q_INVOKABLE QStringList getProvidersNames();

    Q_SIGNAL void providerCountChanges(int providerCount);
    Q_SLOT void saveImage(const QString& providerName, const QString& path);

private:
    QQmlApplicationEngine& m_engine;
    std::list<QPointer<FuncGraphsProvider>> m_providers;
};

#endif //PROVIDER_HANDLER
