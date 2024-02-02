#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QNetworkAccessManager>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onRequestTypeChanged(const QString &selectedMethod);  // Declare your slot here
    void on_submitRequestButton_clicked();
    void onRequestFinished(QNetworkReply *reply);
    void pasteAsPlainText();

private:
    Ui::MainWindow *ui;

    QNetworkAccessManager *networkManager;
};
#endif // MAINWINDOW_H
