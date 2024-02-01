#include "chatgrouplist.h"

#include <QBoxLayout>

#include "../../backend/backend.h"
#include "usergroupboard.h"

/*
 *  好友、群聊列表窗口
 */
ChatGroupList::ChatGroupList(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    {
        this->root_ = new QListWidget(this);
        mainLayout->addWidget(this->root_);
    }
    this->setLayout(mainLayout);

    QObject::connect(this->root_, &QListWidget::itemClicked, this, &ChatGroupList::slot_ListItemClicked);
    QObject::connect(this->root_, &QListWidget::itemDoubleClicked, this, &ChatGroupList::slot_ListItemDClicked);

#ifdef QT_DEBUG
    {

        int num = 1000'0000;
        
        this->AddChatGroup("我的群聊", Backend::GetInstance()->GetGroupFromUid(QString::number(num++)));
        this->AddChatGroup("我的群聊", Backend::GetInstance()->GetGroupFromUid(QString::number(num++)));
        this->AddChatGroup("我的群聊", Backend::GetInstance()->GetGroupFromUid(QString::number(num++)));
        this->AddChatGroup("我的群聊", Backend::GetInstance()->GetGroupFromUid(QString::number(num++)));
    }
#endif
}

void ChatGroupList::AddChatGroup(QString group_str, std::shared_ptr<ChatGroup> chat_group)
{
    auto it = this->groups_.find(group_str);
    if (it == this->groups_.end()) {
        // need new group
        auto _group = std::make_shared<_Group>();

        // add to layout
        _group->header = new PrivateListItem(group_str, true);
        auto header_wid = new FriendListHeader(this);
        _group->header->setSizeHint(QSize{20, 30});
        header_wid->SetGroupName(group_str);
        this->root_->addItem(_group->header);
        this->root_->setItemWidget(_group->header, header_wid);

        // add to data
        this->groups_.insert({group_str, _group});

        // add to layout
        auto index = this->root_->indexFromItem(_group->header);
        auto user_item = new PrivateListItem(group_str, false);
        user_item->setSizeHint(QSize(20, 60));
        auto user_wid = new UserGroupBoard(this);
        user_wid->setMaximumHeight(60);
        user_wid->SetGroup(chat_group);
        this->root_->insertItem(index.row() + 1, user_item);
        this->root_->setItemWidget(user_item, user_wid);

        // add to data
        _group->chat_groups_items.push_back({chat_group, user_item});

        return;
    }

    QVector<_Group::chat_group_item>& users = it->second->chat_groups_items;
    auto user_item = new PrivateListItem(group_str, false);
    user_item->setSizeHint(QSize(20, 60));
    // qDebug() << this->root_->indexFromItem(users[0].item) << users[0].item;

    int index = -1;
    // 寻找最后一个不大于的索引
    for (int i = 0; i < users.size(); ++i) {
        if (users[i].chat_group->Name() > chat_group->Name()) {
            break;
        }
        index = i;
    }
    // qDebug() << "index " << index;
    if (index == -1) {
        index = this->root_->indexFromItem(users[0].item).row();
        users.insert(0, {chat_group, user_item});
    } else {
        int i = index;
        index = this->root_->indexFromItem(users[index].item).row() + 1;
        users.insert(i + 1, {chat_group, user_item});
    }
    // qDebug() << "index " << index;

    // add to layout
    auto user_wid = new UserGroupBoard(this);
    user_wid->setMaximumHeight(60);
    user_wid->SetGroup(chat_group);
    this->root_->insertItem(index, user_item);
    this->root_->setItemWidget(user_item, user_wid);
    if (it->second->folded) {
        user_item->setHidden(true);
    }
}

void ChatGroupList::slot_ListItemClicked(QListWidgetItem *i)
{
    auto item = static_cast<PrivateListItem*>(i);
    if (!item->is_header) {
        qDebug() << "not header";
        return;
    }

    item->SetHidden(!item->IsHidden());
    groups_[item->GroupName()]->folded = item->IsHidden();

    qDebug() << item->GroupName() << " folded : " << item->IsHidden();

    auto& vec = groups_[item->GroupName()]->chat_groups_items;
    for (auto& it : vec) {
        it.item->setHidden(item->IsHidden());
    }
}

void ChatGroupList::slot_ListItemDClicked(QListWidgetItem *i)
{
    auto item = static_cast<PrivateListItem*>(i);
    if (item->is_header) {
        qDebug() << "is header";
        this->slot_ListItemClicked(i);
        return;
    }

    auto widget = this->root_->itemWidget(item);
}
