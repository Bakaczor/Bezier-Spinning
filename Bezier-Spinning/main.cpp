#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QApplication>

#include "SceneManager.h"
#include "ImageProvider.h"
#include "Enums.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QPointer<SceneManager> manager = new SceneManager(nullptr, &app);
    QPointer<ImageProvider> sceneProvider = new ImageProvider(manager->scene);
    QPointer<ImageProvider> imageProvider = new ImageProvider(manager->image);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("SceneManager", manager);
    engine.addImageProvider(QString("SceneProvider"), sceneProvider);
    engine.addImageProvider(QString("ImageProvider"), imageProvider);

    qmlRegisterUncreatableType<Algorithm>("com.algorithm.enum", 1, 0, "Algo", "Cannot create Algorithm in QML");
    qmlRegisterUncreatableType<Animation>("com.animation.enum", 1, 0, "Anim", "Cannot create Animation in QML");

    const QUrl url(u"qrc:/Bezier-Spinning/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl) QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
