#include "grouplist.h"

#include <QBoxLayout>

#include "../../backend/backend.h"
#include "chatgroupboard.h"

/*
 *  好友、群聊列表窗口
 */
GroupList::GroupList(QWidget *parent) : QWidget(parent)
{
    this->root_ = new QTreeWidget(this);
    this->root_->setHeaderHidden(true);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    {
        mainLayout->addWidget(this->root_);
    }
    this->setLayout(mainLayout);

#ifdef QT_DEBUG
    {

        int num = 1000'0000;

        this->AddGroup("我的群聊", Backend::GetInstance()->GetGroupFromUid(QString::number(num++)));
        this->AddGroup("我的群聊", Backend::GetInstance()->GetGroupFromUid(QString::number(num++)));
        this->AddGroup("我的群聊", Backend::GetInstance()->GetGroupFromUid(QString::number(num++)));
        this->AddGroup("我的群聊", Backend::GetInstance()->GetGroupFromUid(QString::number(num++)));
    }
#endif
}

void GroupList::AddGroup(QString party, std::shared_ptr<ChatGroup> group)
{
    auto items = this->root_->findItems(party, Qt::MatchFlag::MatchFixedString);
    auto item = items.empty() ? nullptr : items[0];
    if (item == nullptr) {
        item = new QTreeWidgetItem;
        item->setText(0, party);
        this->root_->addTopLevelItem(item);
    }

    {
        auto n = new QTreeWidgetItem;
        n->setSizeHint(0, {100, 100});
        item->addChild(n);
        ChatGroupBoard* board = new ChatGroupBoard(this);
        board->SetGroup(group);
        this->root_->setItemWidget(n, 0, board);
    }
}

