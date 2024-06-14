#include "session_list.h"

#include <QBoxLayout>
#include <QMenu>

#include "window_manager.h"
#include "backend/backend.h"
#include "shown_board.h"


/*
 *  对话列表窗口
 */
SessionList::SessionList(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    {
        this->root_ = new QListWidget(this);
        mainLayout->addWidget(this->root_);
    }
    this->setLayout(mainLayout);

    QObject::connect(this->root_, &QListWidget::itemClicked, this, &SessionList::slot_ListItemClicked);
    QObject::connect(this->root_, &QListWidget::itemDoubleClicked, this, &SessionList::slot_ListItemDClicked);

    // this->root_->setSelectionMode(QAbstractItemView::NoSelection);

    // todo: update widget and add room api
}

void SessionList::slot_ListItemClicked(QListWidgetItem *i) {}

void SessionList::slot_ListItemDClicked(QListWidgetItem *i) {}
