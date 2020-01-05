#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vehiclesdialog.h"

#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), mdiArea(new QMdiArea)
{
    ui->setupUi(this);

    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);

    readSettings();
}

MainWindow::~MainWindow()
{
    writeSettigns();
    delete ui;
}

void MainWindow::readSettings()
{
    QSettings settins("Sant'Anna Softwores", "Vehicle Expense");
    restoreGeometry(settins.value("geometry", geometry()).toByteArray());
}

void MainWindow::writeSettigns()
{
    QSettings settins("Sant'Anna Softwores", "Vehicle Expense");
    settins.setValue("geometry", saveGeometry());
}

void MainWindow::on_actionVeiculos_triggered()
{
    VehiclesDialog *vehicle = nullptr;

    QList<QMdiSubWindow *> subWindows = mdiArea->subWindowList();
    for (QMdiSubWindow *window: subWindows)
    {
        vehicle = qobject_cast<VehiclesDialog*>(window->widget());
        if (vehicle)
        {
            if (vehicle->isMinimized())
                vehicle->showNormal();
            mdiArea->setActiveSubWindow(window);
        }
    }

    if (!vehicle)
    {
        vehicle = new VehiclesDialog(this);
        connect(vehicle, SIGNAL(rejected()), mdiArea, SLOT(closeActiveSubWindow()));
        mdiArea->addSubWindow(vehicle);
        vehicle->show();
    }
}
