#include "chatsessionlist.h"

#include <QBoxLayout>
#include <QMenu>

#include "../../windowmanager.h"
#include "../../backend/backend.h"
#include "chatgroupboard.h"


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
    ChatGroupBoard* board = new ChatGroupBoard(this);
    board->SetGroup(group);

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
    ChatGroupBoard* board = static_cast<ChatGroupBoard*>(widget);

    WindowManager::GetInstance()->slot_CreateChatSession(board->Group());
}

void ChatSessionList::slot_ListWidRightClicked(const QPoint &pos)
{
    qDebug() << pos;

    auto item = this->list_widget_->itemAt(pos);
    if (item == nullptr) {
        qDebug() << "click item empty";
        return;
    }

    QMenu* menu = new QMenu(this->list_widget_);
    {
        QAction* action_open = new QAction("open");
        connect(action_open, &QAction::triggered, [=] {
            auto index = this->list_widget_->indexFromItem(item);
            qDebug() << index.row();
        });

        menu->addAction(action_open);
    }
    menu->popup(this->list_widget_->mapToGlobal(pos));
}
