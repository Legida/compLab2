#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "FuncGraphsProvider.h"
#include "ProvidersHandler.h"

#include <iostream>
#include <thread>

void createImages(ProvidersHandler& handler) {
    //first image
    auto f1 = [](float x, float y) -> float {
        return 1-x/2-y/4;
    };

    auto f2 = [](float x, float y) -> float {
        return 1+x/2-y/4;
    };

    auto f3 = [](float x, float y) -> float {
        return y;
    };

    auto f4 = [](float x, float y) -> float {
        return 1-x*x-y*y;
    };

    auto f5 = [](float x, float y) -> float {
        return 1-(x-1)*(x-1)-y*y;
    };

    auto triangle = euler::and_f(euler::and_f(f1, f2), f3);
    auto circles = euler::or_f(f4, f5);
    auto res = euler::or_f(std::move(triangle), std::move(circles));

    handler.addProvider(new FuncGraphsProvider("provider1", 100, 100, res));

    //second image
    auto res2 = [](float x, float y) -> float {
        return 1-(x-1)*(x-1)-y*y;
    };

    handler.addProvider(new FuncGraphsProvider("provider2", 100, 100, res2));

    //third image
    auto res3 = [](float x, float y) -> float {
        return y - x;
    };

    handler.addProvider(new FuncGraphsProvider("provider3", 100, 100, res3));
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    ProvidersHandler handler(engine);

    std::thread th1([&handler] (){createImages(handler);});

    const QUrl url(u"qrc:/compLab2/qml/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    int execRes = app.exec();

    th1.join();

    return execRes;
}
