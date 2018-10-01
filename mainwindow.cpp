#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_mailer(new Mailer())
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonSend_clicked()
{
    m_mailer->setLoginStr(ui->lineLogin->text()); // сетим логин
    m_mailer->setPasswordStr(ui->linePassword->text()); // сетим пароль
    m_mailer->setLoginB64(m_mailer->getLoginStr()); // сетим логин в base64
    m_mailer->setPasswordB64(m_mailer->getPasswordStr()); // сетим пароль в base 64
    m_mailer->setMailFrom(ui->lineFrom->text()); // сетим отправителя mailFrom
    m_mailer->setRcptTo(ui->lineTo->text()); // сетим получателя rcptTo
    m_mailer->setSubject(ui->lineSubject->text()); // сетим тему subject
    m_mailer->setMessageText(ui->lineText->toPlainText());

    m_mailer->setFrom(ui->lineFrom->text()); // сетим from: в сообщении
    m_mailer->setTo(ui->lineTo->text()); // сетим to:
    m_mailer->setSubject(ui->lineSubject->text()); // сетим subject:

    m_mailer->clearMessage(); // очищаем сообщение
    m_mailer->createMessage(m_mailer->getFrom(), m_mailer->getTo(), m_mailer->getSubject(), m_mailer->getMessageText(), m_mailer->getEndingDot(), m_mailer->getQuit());
    m_mailer->sendMessage(m_mailer->getMessageStr());
}
