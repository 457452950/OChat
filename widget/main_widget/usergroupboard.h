#ifndef USERGROUPBOARD_H
#define USERGROUPBOARD_H

#include <QLabel>
#include <QWidget>

#include "../../data_structure/datasructures.h"

/*
 *  用户展示面板
 */
class UserGroupBoard : public QWidget {
    Q_OBJECT
public:
    explicit UserGroupBoard(QWidget *parent = nullptr);

    void SetUser(std::shared_ptr<UIUser> user);
    void SetGroup(std::shared_ptr<ChatGroup> user);

    std::shared_ptr<UIUser> GetUser() {return user_;}
    std::shared_ptr<ChatGroup> GetGroup() {return group_;}

    void Refresh();

signals:

private:
    void resizeEvent(QResizeEvent* event) override;

private:
    /* layout */
    // 头像
    QLabel* pix_;
    //
    QLabel* name_;
    // 展示信息
    QLabel* show_label_;

    /* data */
    std::shared_ptr<UIUser> user_;
    std::shared_ptr<ChatGroup> group_;
};


#endif // USERGROUPBOARD_H
