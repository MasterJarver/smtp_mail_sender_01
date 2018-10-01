#ifndef MAILER_H
#define MAILER_H
#include <QByteArray>
#include <QString>

class QSslSocket;
class Mailer
{
private:
    /* Login & Password, buffer */
    QSslSocket* socket; // создаем сокет
    QByteArray recv; // буфер для чтения из сокета
    QString loginStr;  // = "masterjarver@ukr.net"; // принимаем строку с логином
    QByteArray loginB64; // = loginStr.toUtf8().toBase64(); // создаем последовательность байт из логина в Base64
    QString passwordStr; // = "1234512345fff"; // принимаем строку с паролем
    QByteArray passwordB64; // = passwordStr.toUtf8().toBase64(); // создаем последовательность байт из пароля в Base64
    /* SMTP */
    QString host = "smtp.ukr.net"; // хост
    int port = 465; // порт
    /* Authorization & Destination */
    QString ehlo = QString("%1 %2\n").arg("EHLO", loginStr); // просит вернуть доступный сервис
    QString authLogin = "AUTH LOGIN\n"; // запрашивает возможность ввести логин и пароль
    QString mailFrom = "MAIL FROM: masterjarver@ukr.net\n"; // от кого сообщение
    QString rcptTo = "rcpt to: masterjarver@ukr.net\n"; // кому сообщение
    /* data */
    QString data = "data\n"; // запрашивает ввод сообщения
    /* All information in mail */
    QString from; // = "from: masterjarver@ukr.net\n"; // дубликат отправителя
    QString to; // = "to: masterjarver@ukr.net\n"; // дубликат получателя
    QString subject; // = "subject: subject\n"; // тема сообщения
    QString messageText; // = "some message, big messageNEW NEW123 message\n"; // тест сообщения
    QString endingDot = ".\n"; // точка окончания сообщения, ставится после \n
    QString quit = "quit\n"; // выход из smtp
    QString messageStr; // сообщение(включая отправителя, получателя и точку)
    int _test;
public:
    Mailer(); // сигнатура конструктора
    ~Mailer(); // сигнатура деструктора
    void clearMessage(); // очищает сообщение
    QString createMessage(QString from, QString to, QString subject, QString messageText, QString endingDot, QString quit); // функция формирования текста сообщения(с заголовками)
    void sendMessage(QString messageStr);
    QString getLoginStr() const;
    void setLoginStr(const QString &value);
    QString getPasswordStr() const;
    void setPasswordStr(const QString &value);
    QString getMailFrom() const;
    void setMailFrom(const QString &value);
    QString getRcptTo() const;
    void setRcptTo(const QString &value);
    QString getFrom() const;
    void setFrom(const QString &value);
    QString getTo() const;
    void setTo(const QString &value);
    QString getSubject() const;
    void setSubject(const QString &value);
    QString getMessageText() const;
    void setMessageText(const QString &value);
    QByteArray getLoginB64() const;
    void setLoginB64(const QString &value);
    QByteArray getPasswordB64() const;
    void setPasswordB64(const QString &value);
    QString getEndingDot() const;
    QString getQuit() const;
    QString getMessageStr() const;
};
#endif // MAILER_H
