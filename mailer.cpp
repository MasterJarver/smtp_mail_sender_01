#include "mailer.h"
#include <QString>
#include <QSslSocket>
#include <QStringList>

QString Mailer::getLoginStr() const
{
    return loginStr;
}

void Mailer::setLoginStr(const QString &loginStr)
{
    this->loginStr = loginStr;
}

QString Mailer::getPasswordStr() const
{
    return passwordStr;
}

void Mailer::setPasswordStr(const QString &passwordStr)
{
    this->passwordStr = passwordStr;
}

QString Mailer::getMailFrom() const
{
    return mailFrom;
}

void Mailer::setMailFrom(const QString &mailFrom)
{
    this->mailFrom = "MAIL FROM: " + mailFrom + "\n";
}

QString Mailer::getRcptTo() const
{
    return rcptTo;
}

void Mailer::setRcptTo(const QString &rcptTo)
{
    this->rcptTo = "rcpt to: " + rcptTo + "\n";
}

QString Mailer::getFrom() const
{
    return from;
}

void Mailer::setFrom(const QString &from)
{
    this->from = "from: " + from + "\n";
}

QString Mailer::getTo() const
{
    return to;
}

void Mailer::setTo(const QString &to)
{
    this->to = "to: " + to + "\n";
}

QString Mailer::getSubject() const
{
    return subject;
}

void Mailer::setSubject(const QString &subject)
{
    this->subject = "subject: " + subject + "\n";
}

QString Mailer::getMessageText() const
{
    return messageText;
}

void Mailer::setMessageText(const QString &messageText)
{
    this->messageText = messageText + "\n";
}

QByteArray Mailer::getLoginB64() const
{
    return loginB64;
}

void Mailer::setLoginB64(const QString &loginStr)
{
    loginB64 = loginStr.toUtf8().toBase64();
}

QByteArray Mailer::getPasswordB64() const
{
    return passwordB64;
}

void Mailer::setPasswordB64(const QString &passwordB64)
{
    this->passwordB64 = passwordB64.toUtf8().toBase64();
}

QString Mailer::getEndingDot() const
{
    return endingDot;
}

QString Mailer::getQuit() const
{
    return quit;
}

QString Mailer::getMessageStr() const
{
    return messageStr;
}

Mailer::Mailer():
    socket(new QSslSocket)// конструктор
{

}
Mailer::~Mailer() // деструктор
{

}
void Mailer::clearMessage() // очищает сообщение
{
    this->messageStr = "";
}
QString Mailer::createMessage(QString from, QString to, QString subject, QString messageText, QString endingDot, QString quit) // формирует текст сообщения с заголовками
{
    this->messageStr.append(from);
    this->messageStr.append(to);
    this->messageStr.append(subject);
    this->messageStr.append(messageText);
    this->messageStr.append(endingDot);
    this->messageStr.append(quit);
    return this->messageStr;
}
void Mailer::sendMessage(QString messageStr)
{
    socket->connectToHostEncrypted(host, port); // коннектимся к хосту
    socket->waitForEncrypted();
    socket->write(ehlo.toUtf8()); // пишем в сокет
    socket->waitForBytesWritten();
    bool connected = socket->waitForReadyRead(); // ждем, пока приконнектимся
    qDebug() << "connected to: " << host << connected;
    recv = socket->readAll(); // читаем инфу о сервере
    QString s = QString::fromUtf8(recv); // конвертируем последовательность байт в строку
    qDebug() << s;
    socket->waitForReadyRead(); // ждем возможности чтения 2й раз
    recv = socket->readAll(); // читаем доступный сервис
    s = QString::fromUtf8(recv);
    QStringList list = s.split("\n");
    for(int i = 0; i < list.length() - 1; i++)
    {
        qDebug() << list[i]; // выводим на консоль буфер
    }
    /* ==========авторизация========== */
    socket->write(authLogin.toLatin1()); // запрашиваем ввод логина и пароля
    socket->waitForBytesWritten();
    socket->waitForReadyRead();
    recv = socket->readAll(); // прочитали 334 U6
    qDebug() << authLogin;

    socket->write(loginB64 + "\n"); // пишем логин в base64
    qDebug() << loginB64;
    socket->waitForBytesWritten();
    socket->waitForReadyRead();
    recv = socket->readAll();
    qDebug() << recv; // прочитали 334 Q6

    socket->write(passwordB64 + "\n"); // пишем пароль в base64
    qDebug() << passwordB64;
    socket->waitForBytesWritten();
    socket->waitForReadyRead();
    recv = socket->readAll();
    qDebug() << recv; // Authentication succeeded

    socket->write(mailFrom.toUtf8()); // пишем от кого mail
    qDebug() << mailFrom;
    socket->waitForBytesWritten();
    socket->waitForReadyRead();
    recv = socket->readAll();
    qDebug() << recv; // 250 OK

    socket->write(rcptTo.toUtf8()); // кому отправляем mail
    qDebug() << rcptTo;
    socket->waitForBytesWritten();
    socket->waitForReadyRead();
    recv = socket->readAll();
    qDebug() << recv; // 250 Accepted

    socket->write(data.toUtf8()); // пишем data для ввода сообщения
    qDebug() << data;
    socket->waitForBytesWritten();
    socket->waitForReadyRead();
    recv = socket->readAll();
    qDebug() << recv; // 354 Enter message, ending with "." on a line by itself

    socket->write(messageStr.toUtf8()); // пишем сообщение включая отправителя получателя и точку
    qDebug() << messageStr;
    socket->waitForBytesWritten();
    socket->waitForReadyRead();
    recv = socket->readAll();
    qDebug() << recv; // 250 OK id=1g5XGV-000EaO-9P

    socket->write(quit.toUtf8()); // пишем quit для выхода из сервиса
    qDebug() << quit;
    socket->waitForBytesWritten();
    socket->waitForReadyRead();
    recv = socket->readAll();
    qDebug() << recv; // 354 Enter message, ending with "." on a line by itself

    socket->close(); // закрываем сокет
    qDebug() << "close";
    delete socket; // освобождаем память
}
