#ifndef GROUPLIST_H
#define GROUPLIST_H

#include <QTreeWidget>
#include <QWidget>


#include "../../data_structure/datasructures.h"

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


#endif // GROUPLIST_H
