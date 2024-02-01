#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect the QComboBox signal to a slot
    connect(ui->requestTypeComboBox, &QComboBox::currentTextChanged,
            this, &MainWindow::onRequestTypeChanged);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onRequestTypeChanged(const QString &selectedMethod) {
    // qDebug() << "Selected HTTP Method:" << selectedMethod;

    if (selectedMethod == "GET") {
        // Handle GET request logic
        qDebug() << "Selected HTTP Method:" << selectedMethod;

    } else if (selectedMethod == "POST") {
        // Handle POST request logic
        qDebug() << "Selected HTTP Method:" << selectedMethod;

    }
    // ... and so on for other methods
}