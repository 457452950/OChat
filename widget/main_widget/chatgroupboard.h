#ifndef CHATGROUPBOARD_H
#define CHATGROUPBOARD_H

#include <QLabel>
#include <QWidget>

#include "../../data_structure/datasructures.h"

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

#endif // CHATGROUPBOARD_H
