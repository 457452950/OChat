#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPicture>
#include <QLabel>
#include <QListWidget>
#include <QTreeWidget>

#include <memory>

#include "../data_structure/datasructures.h"

class UserBoard : public QWidget {
    Q_OBJECT
public:
    explicit UserBoard(QWidget *parent = nullptr);

    void SetUser(std::shared_ptr<User> user);

    void Update();

signals:

private:
    /* layout */
    // 头像
    QLabel* user_pix_;
    //
    QLabel* user_name_;
    // 展示信息
    QLabel* show_label_;

    // data
    std::shared_ptr<User> user_;
};

class ChatSessionList : public QWidget {
    Q_OBJECT
public:
    explicit ChatSessionList(QWidget *parent = nullptr);

    void AddUser(std::shared_ptr<User> user);

signals:

private:
    void slot_ItemDoubleClicked(QListWidgetItem *item);
    void slot_ListWidRightClicked(const QPoint& pos);
    void slot_ItemMenu();

private:
    QListWidget* list_widget_;
};

class UserList : public QWidget {
    Q_OBJECT
public:
    explicit UserList(QWidget *parent = nullptr);

    void AddUser(QString party,  std::shared_ptr<User> user);

signals:

private:
    QTreeWidget* root_;
};

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(std::shared_ptr<User> master, QWidget *parent = nullptr);

signals:

private:
    // layout
    UserBoard* master_board_;
    ChatSessionList *user_list_;
    UserList* friend_list_;
    UserList* class_list_;

    // data
    std::shared_ptr<User> master_user_;
};

#endif // MAINWIDGET_H
