#ifndef CHATSESSIONLIST_H
#define CHATSESSIONLIST_H

#include <QListWidget>
#include <QWidget>

#include "../../data_structure/datasructures.h"

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


#endif // CHATSESSIONLIST_H
