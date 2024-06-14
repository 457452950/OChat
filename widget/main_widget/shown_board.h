#ifndef OCHAT__WIDGET_MAIN_WIDGET__USERGROUP_BOARD_H
#define OCHAT__WIDGET_MAIN_WIDGET__USERGROUP_BOARD_H

#include <QLabel>
#include <QWidget>

#include "widget/wrapper.h"


/*
 *  用户展示面板
 */
class ShownBoard : public QWidget, public ObjectChangeList::Listener {
    Q_OBJECT
public:
    explicit ShownBoard(QWidget *parent = nullptr);
    ~ShownBoard();

    void SetUser(const QString &uid);
    void SetRoom(const QString &uid);

    QString GetUid() { return shown_uid_; }

    void Refresh(const User &user);
    void Refresh(const ChatRoom &room);

private:
    void resizeEvent(QResizeEvent *event) override;

    void OnUserUpdate(const User &user) override { this->Refresh(user); }
    void OnChatRoomUpdate(const ChatRoom &room) override { this->Refresh(room); }

private:
    /* layout */
    // 头像
    QLabel *pix_;
    //
    QLabel *name_;
    // 展示信息
    QLabel *show_label_;

    QString shown_uid_;
};


#endif // OCHAT__WIDGET_MAIN_WIDGET__USERGROUP_BOARD_H
