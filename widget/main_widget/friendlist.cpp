#include "friendlist.h"

#include <QBoxLayout>

#include "../../backend/backend.h"
#include "userboard.h"


/*
 *  好友、群聊列表窗口
 */
FriendList::FriendList(QWidget *parent) : QWidget(parent)
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
        auto user = Backend::GetInstance()->GetUserFromUid("10001");
        this->AddUser("我的好友", user);
    }
#endif
}

void FriendList::AddUser(QString party, std::shared_ptr<User> user)
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
        UserBoard* board = new UserBoard(this);
        board->SetUser(user);
        this->root_->setItemWidget(n, 0, board);
    }
}
