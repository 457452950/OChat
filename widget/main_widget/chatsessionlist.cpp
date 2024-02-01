#include "chatsessionlist.h"

#include <QBoxLayout>
#include <QMenu>

#include "../../windowmanager.h"
#include "../../backend/backend.h"
#include "usergroupboard.h"


/*
 *  对话列表窗口
 */
ChatSessionList::ChatSessionList(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->setContentsMargins(0, 0,0,0);
    {
        this->list_widget_ = new QListWidget(this);
        list_widget_->setDragDropMode(QAbstractItemView::InternalMove);
        list_widget_->setResizeMode(QListView::Adjust);
        list_widget_->setFrameShape(QFrame::NoFrame);
        mainLayout->addWidget(this->list_widget_);

    }
    this->setLayout(mainLayout);

    QObject::connect(this->list_widget_, &QListWidget::itemDoubleClicked, this, &ChatSessionList::slot_ItemDoubleClicked);

    this->list_widget_->setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(this->list_widget_, &QListWidget::customContextMenuRequested, this, &ChatSessionList::slot_ListWidRightClicked);

    /* init menu */
    menu_ = new QMenu(this);
    {
        QAction* action_open = new QAction("对话");
        connect(action_open, &QAction::triggered, [this] {
            if (this->current_item_)
                this->slot_ItemDoubleClicked(this->current_item_);
        });
        menu_->addAction(action_open);
    }
    {
        QAction* action_drop = new QAction("drop");
        connect(action_drop, &QAction::triggered, [this] {
            if (this->current_item_) {
                auto wid = this->list_widget_->itemWidget(this->current_item_);
                UserGroupBoard* board = static_cast<UserGroupBoard*>(wid);
                auto group = board->GetGroup();
                Q_ASSERT(group);
                this->list_widget_->removeItemWidget(this->current_item_);

                delete this->current_item_;
                delete wid;

                this->current_item_ = nullptr;

                WindowManager::GetInstance()->slot_DestroyChatSession(group->Uid());
            }
        });
        menu_->addAction(action_drop);
    }

#ifdef QT_DEBUG
    {
        int num = 1000'0000;
        this->AddChatSession(Backend::GetInstance()->GetGroupFromUid(QString::number(num++)));
        this->AddChatSession(Backend::GetInstance()->GetGroupFromUid(QString::number(num++)));
        this->AddChatSession(Backend::GetInstance()->GetGroupFromUid(QString::number(num++)));
        this->AddChatSession(Backend::GetInstance()->GetGroupFromUid(QString::number(num++)));
    }
#endif
}

void ChatSessionList::AddChatSession(std::shared_ptr<ChatGroup> group)
{
    UserGroupBoard* board = new UserGroupBoard(this);
    board->SetGroup(group);
    board->setMaximumHeight(90);

    QListWidgetItem* item = new QListWidgetItem;
    item->setSizeHint({0, 90});

    this->list_widget_->addItem(item);
    this->list_widget_->setItemWidget(item, board);
}

void ChatSessionList::slot_ItemDoubleClicked(QListWidgetItem *item)
{
    auto index = this->list_widget_->indexFromItem(item);

    qDebug() << "item double clicked " << item->text() << " " << index.row();

    QWidget* widget = this->list_widget_->itemWidget(item);
    UserGroupBoard* board = static_cast<UserGroupBoard*>(widget);

    WindowManager::GetInstance()->slot_CreateChatSession(board->GetGroup());
}

void ChatSessionList::slot_ListWidRightClicked(const QPoint &pos)
{
    qDebug() << pos;

    auto item = this->list_widget_->itemAt(pos);
    if (item == nullptr) {
        qDebug() << "click item empty";
        return;
    }
    current_item_ = item;

    menu_->popup(this->list_widget_->mapToGlobal(pos));
}
