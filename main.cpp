#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <wrapper.h>
#include <systeminfo.h>
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    systeminfo *sinfo = new systeminfo();
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    auto test = engine.findChild<QObject*>("mytestview");
    qDebug() << test;
    auto wrapper = new Wrapper();
    wrapper->setID(sinfo->calculateID());
    wrapper->setName(sinfo->getRAMName());
    QObject::connect(engine.rootObjects().first(), SIGNAL(startBench()), wrapper, SLOT(start()));
    engine.rootContext()->setContextProperty("backend", wrapper);
    engine.rootContext()->setContextProperty("sinfo", sinfo);
    return app.exec();
}
