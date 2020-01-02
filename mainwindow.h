#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QMdiArea;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionVeiculos_triggered();

private:
    Ui::MainWindow *ui;
    QMdiArea *mdiArea;

    void readSettings();
    void writeSettigns();
};

#endif // MAINWINDOW_H
