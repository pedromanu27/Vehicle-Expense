#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QDebug>

#include "database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);    
    a.setOrganizationName("Walk");
    a.setApplicationName("Vehicle Expense");
    a.setApplicationDisplayName("Vehicle Expense");
    a.setApplicationVersion("1.0.0");
    a.setStyle("fusion");

    QPixmap pixmap(":/images/splash.jpg");
    QSplashScreen *splash = new QSplashScreen(pixmap);
    splash->show();

    splash->showMessage("Carregando Modulos!", Qt::AlignRight | Qt::AlignTop, Qt::white);

    a.processEvents();
    //if (!createConnection())
    //    return 1;

    MainWindow w;
    w.setWindowTitle("");
    w.show();

    splash->showMessage("Conexão Estabelecida!",  Qt::AlignRight | Qt::AlignTop, Qt::white);
    splash->finish(&w);
    delete splash;

    return a.exec();
}
