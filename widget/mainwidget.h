#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPicture>
#include <QLabel>
#include <QListWidget>
#include <QTreeWidget>
#include <QCloseEvent>

#include <memory>

#include "../data_structure/datasructures.h"

/*
 *  用户展示面板
 */
class UserBoard : public QWidget {
    Q_OBJECT
public:
    explicit UserBoard(QWidget *parent = nullptr);

    void SetUser(std::shared_ptr<User> user);

    void Refresh();

signals:

private:
    /* layout */
    // 头像
    QLabel* user_pix_;
    //
    QLabel* user_name_;
    // 展示信息
    QLabel* show_label_;

    /* data */
    std::shared_ptr<User> user_;
};

/*
 *  对话群聊展示面板
 */
class ChatGroupBoard : public QWidget {
    Q_OBJECT
public:
    explicit ChatGroupBoard(QWidget *parent = nullptr);

    void SetGroup(std::shared_ptr<ChatGroup> group);
    std::shared_ptr<ChatGroup> Group() const;

    void Refresh();


signals:

private:
    /* layout */
    // 头像
    QLabel* group_pix_;
    //
    QLabel* group_name_;
    // 展示信息
    QLabel* show_label_;

    /* data */
    std::shared_ptr<ChatGroup> group_;
};


/*
 *  对话列表窗口
 */
class ChatSessionList : public QWidget {
    Q_OBJECT
public:
    explicit ChatSessionList(QWidget *parent = nullptr);

    void AddChatSession(std::shared_ptr<ChatGroup> group);

signals:

private:
    void slot_ItemDoubleClicked(QListWidgetItem *item);
    void slot_ListWidRightClicked(const QPoint& pos);
    void slot_ItemMenu();

private:
    // layout
    QListWidget* list_widget_;
};

/*
 *  好友列表窗口
 */
class FriendList : public QWidget {
    Q_OBJECT
public:
    explicit FriendList(QWidget *parent = nullptr);

    void AddUser(QString party,  std::shared_ptr<User> user);

signals:

private:
    // layout
    QTreeWidget* root_;
};

/*
 *  群聊列表窗口
 */
class GroupList : public QWidget {
    Q_OBJECT
public:
    explicit GroupList(QWidget *parent = nullptr);

    void AddGroup(QString party, std::shared_ptr<ChatGroup> group);

signals:

private:
    // layout
    QTreeWidget* root_;
};

/*
 *  主页面
 */
class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(std::shared_ptr<User> master, QWidget *parent = nullptr);

signals:

private:
    void closeEvent(QCloseEvent* event);


private:
    // layout
    UserBoard* master_board_;
    ChatSessionList *user_list_;
    FriendList* friend_list_;
    GroupList* class_list_;

    // data
    std::shared_ptr<User> master_user_;
};

#endif // MAINWIDGET_H
