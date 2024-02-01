#include "friendlist.h"

#include <QBoxLayout>

#include <tuple>

#include "../../backend/backend.h"
#include "../../windowmanager.h"
#include "usergroupboard.h"

/**
 * 列表头
 */
FriendListHeader::FriendListHeader(QWidget *parent)
    :QWidget(parent)
{
    QHBoxLayout* main_layout = new QHBoxLayout(this);
    main_layout->setContentsMargins(0, 0, 0, 0);
    {
        arrow_ = new QLabel(this);
        arrow_->setPixmap(QPixmap(":/image/resource/image/arrow_down.png"));
        arrow_->setScaledContents(true);
        arrow_->setFixedSize({9, 9});
        main_layout->addWidget(arrow_);

        group_name_ = new QLabel("分组名", this);
        main_layout->addWidget(group_name_);

        QSpacerItem* space = new QSpacerItem(9999, 0, QSizePolicy::Maximum, QSizePolicy::Minimum);
        main_layout->addSpacerItem(space);
    }
    this->setLayout(main_layout);
}

void FriendListHeader::SetGroupName(const QString &name)
{
    this->group_name_->setText(name);
}


/*
 *  好友、群聊列表窗口
 */
FriendList::FriendList(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    {
        this->root_ = new QListWidget(this);
        mainLayout->addWidget(this->root_);
    }
    this->setLayout(mainLayout);

    QObject::connect(this->root_, &QListWidget::itemClicked, this, &FriendList::slot_ListItemClicked);
    QObject::connect(this->root_, &QListWidget::itemDoubleClicked, this, &FriendList::slot_ListItemDClicked);

#ifdef QT_DEBUG
    {
        auto user = Backend::GetInstance()->GetUserFromUid("10001");
        this->AddUser("我的好友", user);

        user = Backend::GetInstance()->GetUserFromUid("10000");
        this->AddUser("我的好友", user);
    }
#endif

    // this->root_->setSelectionMode(QAbstractItemView::NoSelection);
}

void FriendList::AddUser(QString group_str, std::shared_ptr<User> user)
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
        user_wid->SetUser(user);
        this->root_->insertItem(index.row() + 1, user_item);
        this->root_->setItemWidget(user_item, user_wid);

        // add to data
        _group->users_items.push_back({user, user_item});

        return;
    }

    QVector<_Group::user_item>& users = it->second->users_items;
    auto user_item = new PrivateListItem(group_str, false);
    user_item->setSizeHint(QSize(20, 60));
    // qDebug() << this->root_->indexFromItem(users[0].item) << users[0].item;

    int index = -1;
    // 寻找最后一个不大于的索引
    for (int i = 0; i < users.size(); ++i) {
        if (users[i].user->Name() > user->Name()) {
            break;
        }
        index = i;
    }
    // qDebug() << "index " << index;
    if (index == -1) {
        index = this->root_->indexFromItem(users[0].item).row();
        users.insert(0, {user, user_item});
    } else {
        int i = index;
        index = this->root_->indexFromItem(users[index].item).row() + 1;
        users.insert(i + 1, {user, user_item});
    }
    // qDebug() << "index " << index;

    // add to layout
    auto user_wid = new UserGroupBoard(this);
    user_wid->setMaximumHeight(60);
    user_wid->SetUser(user);
    this->root_->insertItem(index, user_item);
    this->root_->setItemWidget(user_item, user_wid);
    if (it->second->folded) {
        user_item->setHidden(true);
    }
}

void FriendList::slot_ListItemClicked(QListWidgetItem *i)
{
    auto item = static_cast<PrivateListItem*>(i);
    if (!item->is_header) {
        qDebug() << "not header";
        return;
    }

    item->SetHidden(!item->IsHidden());
    groups_[item->GroupName()]->folded = item->IsHidden();

    qDebug() << item->GroupName() << " folded : " << item->IsHidden();

    auto& vec = groups_[item->GroupName()]->users_items;
    for (auto& it : vec) {
        it.item->setHidden(item->IsHidden());
    }
}

void FriendList::slot_ListItemDClicked(QListWidgetItem *i)
{
    auto item = static_cast<PrivateListItem*>(i);
    if (item->is_header) {
        qDebug() << "is header";
        this->slot_ListItemClicked(i);
        return;
    }

    auto widget = this->root_->itemWidget(item);
}
