#ifndef FRIENDLIST_H
#define FRIENDLIST_H

#include <QTreeWidget>
#include <QWidget>

#include "../../data_structure/datasructures.h"

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

#endif // FRIENDLIST_H
