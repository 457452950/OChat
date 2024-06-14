#include "friend_list.h"

#include <QBoxLayout>

#include <tuple>

#include "backend/backend.h"


/*
 *  好友、群聊列表窗口
 */
FriendList::FriendList(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    {
        this->root_ = new QListWidget(this);
        mainLayout->addWidget(this->root_);
    }
    this->setLayout(mainLayout);

    QObject::connect(this->root_, &QListWidget::itemClicked, this, &FriendList::slot_ListItemClicked);
    QObject::connect(this->root_, &QListWidget::itemDoubleClicked, this, &FriendList::slot_ListItemDClicked);

    // this->root_->setSelectionMode(QAbstractItemView::NoSelection);

    // todo: update widget and add user api
}

void FriendList::slot_ListItemClicked(QListWidgetItem *i) {}

void FriendList::slot_ListItemDClicked(QListWidgetItem *i) {}
