#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QDebug>

#include "database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap(":/images/splash.jpg");
    QSplashScreen *splash = new QSplashScreen(pixmap);
    splash->show();

    splash->showMessage("Carregando Modulos!", Qt::AlignRight | Qt::AlignTop, Qt::white);

    a.processEvents();
    if (!createConnection())
        return 1;

    MainWindow w;
    w.show();

    splash->showMessage("Conexão Estabelecida!",  Qt::AlignRight | Qt::AlignTop, Qt::white);
    splash->finish(&w);
    delete splash;

    return a.exec();
}
