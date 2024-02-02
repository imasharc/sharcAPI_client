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
    QString url = ui->inputTextEdit->toPlainText(); // Get URL from the input field
    QUrl qurl(url);

    if (!qurl.isValid()) {
        qDebug() << "Invalid URL:" << url;
        return;
    }

    QString method = ui->requestTypeComboBox->currentText();
    QNetworkRequest request(qurl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    if (method == "GET") {
        networkManager->get(request); // Send GET request
    } else if (method == "POST") {
        QString jsonBody = ui->bodyTextEdit->toPlainText(); // Assuming jsonTextEdit is the QTextEdit where users enter JSON
        QByteArray postData = jsonBody.toUtf8();
        networkManager->post(request, postData); // Send POST request with JSON body
    }

    // QNetworkRequest request(qurl);

    networkManager->get(request); // Send GET request
}

void MainWindow::onRequestFinished(QNetworkReply *reply) {
    if (reply->error()) {
        qDebug() << "Request failed: " << reply->errorString();
        QString errorResponse = "<span style='color: red;'>Error: " + reply->errorString() + "<br>" + reply->readAll() + "</span>";
        ui->responseTextBrowser->setHtml(errorResponse); // Display error response
    } else {
        QString response = QString(reply->readAll());
        qDebug() << "Response:" << response;

        ui->responseTextBrowser->setText(response);
    }

    reply->deleteLater();
}

