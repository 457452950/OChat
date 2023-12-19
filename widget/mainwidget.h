#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPicture>
#include <QLabel>
#include <QListWidget>
#include <QTreeWidget>

class UserBoard : public QWidget {
    Q_OBJECT
public:
    explicit UserBoard(QWidget *parent = nullptr);

    void SetName(QString name);
    void SetSignature(QString signature);

signals:

private:
    QLabel* user_pix_;
    QLabel* user_name_;
    QLabel* user_signature_;
};

class ChatSessionList : public QWidget {
    Q_OBJECT
public:
    explicit ChatSessionList(QWidget *parent = nullptr);

    void AddUser(QString name, QString signature);

signals:

private:
    QListWidget* list_widget_;
};

class UserList : public QWidget {
    Q_OBJECT
public:
    explicit UserList(QWidget *parent = nullptr);

    void AddUser(QString party, QString name, QString signature);

signals:

private:
    QTreeWidget* root_;
};

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);

signals:

private:
    UserBoard* user_board_;
    ChatSessionList *user_list_;
    UserList* friend_list_;
    UserList* class_list_;
};

#endif // MAINWIDGET_H
