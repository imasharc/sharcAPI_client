#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect the QComboBox signal to a slot
    connect(ui->requestTypeComboBox, &QComboBox::currentTextChanged,
            this, &MainWindow::onRequestTypeChanged);

    connect(ui->submitRequestButton, &QPushButton::clicked, this, &MainWindow::on_submitRequestButton_clicked);

    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onRequestFinished);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onRequestTypeChanged(const QString &selectedMethod) {

    if (selectedMethod == "GET") {
        // Handle GET request logic
        qDebug() << "Selected HTTP Method:" << selectedMethod;

    } else if (selectedMethod == "POST") {
        // Handle POST request logic
        qDebug() << "Selected HTTP Method:" << selectedMethod;

    }
    // ... and so on for other methods
}

void MainWindow::on_submitRequestButton_clicked()
{
    ui->responseTextBrowser->setText("Test static text");

    QString url = ui->inputTextEdit->toPlainText(); // Get URL from the input field
    QUrl qurl(url);

    // Ensure the URL is valid
    if (!qurl.isValid()) {
        qDebug() << "Invalid URL:" << url;
        return;
    }

    QNetworkRequest request(qurl);

    networkManager->get(request); // Send GET request
}

void MainWindow::onRequestFinished(QNetworkReply *reply) {
    if (reply->error()) {
        qDebug() << "Request failed: " << reply->errorString();
        qDebug() << "Server replied: " << reply->readAll(); // This may contain useful error information
    } else {
        QString response = QString(reply->readAll());
        qDebug() << "Response:" << response;

        ui->responseTextBrowser->setText(response);
    }

    reply->deleteLater();
}

