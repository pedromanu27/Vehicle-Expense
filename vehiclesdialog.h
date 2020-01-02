#ifndef VEHICLESDIALOG_H
#define VEHICLESDIALOG_H

#include <QDialog>

class QSqlTableModel;
class QDataWidgetMapper;
class QTableView;
class QDialogButtonBox;

class VehiclesDialog : public QDialog
{
    Q_OBJECT
public:
    explicit VehiclesDialog(QWidget *parent = nullptr);

private:
    QSqlTableModel *model;
    QTableView *view;

    void setupModel();
    void setupView();
    QDialogButtonBox *createButtons();

signals:

public slots:
};

#endif // VEHICLESDIALOG_H
