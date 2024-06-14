#include "room_list.h"

#include <QBoxLayout>

#include "../../backend/backend.h"
#include "shown_board.h"

/*
 *  群聊列表窗口
 */
RoomList::RoomList(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    {
        this->root_ = new QListWidget(this);
        mainLayout->addWidget(this->root_);
    }
    this->setLayout(mainLayout);

    QObject::connect(this->root_, &QListWidget::itemClicked, this, &RoomList::slot_ListItemClicked);
    QObject::connect(this->root_, &QListWidget::itemDoubleClicked, this, &RoomList::slot_ListItemDClicked);

    // this->root_->setSelectionMode(QAbstractItemView::NoSelection);

    // todo: update widget and add room api
}

void RoomList::slot_ListItemClicked(QListWidgetItem *i) {}

void RoomList::slot_ListItemDClicked(QListWidgetItem *i) {}
