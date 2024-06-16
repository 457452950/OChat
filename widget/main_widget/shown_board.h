#ifndef OCHAT__WIDGET_MAIN_WIDGET__USERGROUP_BOARD_H
#define OCHAT__WIDGET_MAIN_WIDGET__USERGROUP_BOARD_H

#include <QLabel>
#include <QWidget>

#include <lazybox/Assert.hpp>

#include "widget/wrapper.h"
#include "backend/backend.h"

/*
 *  用户展示面板
 */
class ShownBoard : public QWidget, public EventWrapperManager::Listener {
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

    void OnObjectUpdate(const ChangeEvent &event) override {
        if(event.type == Mod) {
            if(shown_user_) {
                auto user = Backend::GetInstance()->GetUser(event.uid);
                Assert(user, "user not found");
                this->Refresh(*user);
            } else {
                auto room = Backend::GetInstance()->GetRoom(event.uid);
                Assert(room, "user not found");
                this->Refresh(*room);
            }
        }
    }

private:
    /* layout */
    // 头像
    QLabel *pix_;
    //
    QLabel *name_;
    // 展示信息
    QLabel *show_label_;

    bool    shown_user_{true};
    QString shown_uid_;
};


#endif // OCHAT__WIDGET_MAIN_WIDGET__USERGROUP_BOARD_H
