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

#include "main_widget/chatsessionlist.h"
#include "main_widget/friendlist.h"
#include "main_widget/grouplist.h"
#include "main_widget/userboard.h"


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
