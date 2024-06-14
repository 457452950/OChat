#ifndef OCHAT__WIDGET__MAIN_WIDGET_H
#define OCHAT__WIDGET__MAIN_WIDGET_H

#include <QWidget>
#include <QPicture>
#include <QLabel>
#include <QListWidget>
#include <QTreeWidget>
#include <QCloseEvent>

#include <memory>

#include "widget/wrapper.h"

#include "main_widget/session_list.h"
#include "main_widget/friend_list.h"
#include "main_widget/room_list.h"
#include "main_widget/shown_board.h"


/*
 *  主页面
 */
class MainWidget : public QWidget, public ObjectChangeList::Listener {
    Q_OBJECT
public:
    explicit MainWidget(const User &master, QWidget *parent = nullptr);
    ~MainWidget();

signals:

private:
    void closeEvent(QCloseEvent *event) override;

    void OnUserUpdate(const User &user) override;

private:
    // layout
    ShownBoard  *master_board_;
    SessionList *user_list_;
    FriendList  *friend_list_;
    RoomList    *room_list_;

    // data
    User master_user_;
};

#endif // OCHAT__WIDGET__MAIN_WIDGET_H
