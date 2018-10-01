#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <memory>
#include <QMainWindow>
#include "mailer.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_buttonSend_clicked();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<Mailer> m_mailer;
};

#endif // MAINWINDOW_H
