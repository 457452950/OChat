#ifndef USERBOARD_H
#define USERBOARD_H

#include <QLabel>
#include <QWidget>

#include "../../data_structure/datasructures.h"

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


#endif // USERBOARD_H
