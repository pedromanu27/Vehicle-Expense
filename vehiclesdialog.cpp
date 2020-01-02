#include "vehiclesdialog.h"

#include <QSqlTableModel>
#include <QTableView>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QPushButton>

VehiclesDialog::VehiclesDialog(QWidget *parent)
    : QDialog(parent)
{
    setupModel();
    setupView();

    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(view);
    mainLayout->addWidget(createButtons());
    setLayout(mainLayout);
}

void VehiclesDialog::setupModel()
{
    model = new QSqlTableModel(this);
    model->setTable("vehicles");
    model->setEditStrategy(QSqlTableModel::OnRowChange);
    model->select();
}

void VehiclesDialog::setupView()
{
    view = new QTableView(this);
    view->setModel(model);
    view->setEditTriggers(QTableView::NoEditTriggers);
    view->setSelectionMode(QTableView::SingleSelection);
    view->setSelectionBehavior(QTableView::SelectRows);
    view->setColumnHidden(0, true);
}


QDialogButtonBox * VehiclesDialog::createButtons()
{
    QPushButton *addButton = new QPushButton(tr("&Adicionar"));
    QPushButton *editButton = new QPushButton( tr("&Editar"));
    QPushButton *removeButton = new QPushButton( tr("&Remover"));
    QPushButton *closeButton = new QPushButton( tr("&Fechar"));

    closeButton->setDefault(true);

    connect(closeButton, &QAbstractButton::clicked, this, &QDialog::close);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(this);
    buttonBox->addButton(addButton, QDialogButtonBox::ResetRole);
    buttonBox->addButton(editButton, QDialogButtonBox::ResetRole);
    buttonBox->addButton(removeButton, QDialogButtonBox::ResetRole);
    buttonBox->addButton(closeButton, QDialogButtonBox::RejectRole);
    return buttonBox;
}
