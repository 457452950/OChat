#include "mainwidget.h"

#include <QPixmap>
#include <QImage>
#include <QBoxLayout>
#include <QMenu>
#include <QMessageBox>

#include "../windowmanager.h"
#include "../config/clientsetting.h"
#include "../cache/datacache.h"

/*
 *  用户展示面板
 */
UserBoard::UserBoard(QWidget* parent)
    : QWidget(parent)
{
    auto img = DataCache::GetInstance()->GetImage("H:/Resources/image/awesomeface.png");
    auto&& img2 = img->scaled({80, 80});

    this->user_pix_ = new QLabel(this);
    this->user_pix_->setPixmap(QPixmap::fromImage(*img));
    {
        this->user_pix_->setFixedSize({80, 80});
    }

    this->user_name_ = new QLabel("name", this);
    this->show_label_ = new QLabel("label", this);
    {
        auto font = this->user_name_->font();
        font.setPointSize(14);
        font.setBold(true);
        this->user_name_->setFont(font);
        this->user_name_->setAlignment(Qt::AlignLeft);
    }
    {
        auto font = this->show_label_->font();
        font.setPointSize(10);
        this->show_label_->setFont(font);
        this->show_label_->setAlignment(Qt::AlignLeft);
    }

    QHBoxLayout* mainLayout = new QHBoxLayout;
    {
        mainLayout->setSpacing(25);

        mainLayout->addWidget(user_pix_);

        QVBoxLayout* subLayout = new QVBoxLayout;
        {
            subLayout->setSpacing(0);

            subLayout->addWidget(user_name_);
            subLayout->addWidget(show_label_);
            subLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
        }
        mainLayout->addLayout(subLayout);
    }
    this->setLayout(mainLayout);
}

void UserBoard::SetUser(std::shared_ptr<User> user)
{
    this->user_ = user;
    this->Refresh();
}

void UserBoard::Refresh()
{
    if (this->user_ == nullptr) {
        return;
    }

    this->user_name_->setText(this->user_->UserName());
    this->show_label_->setText(this->user_->Signature());


    auto img = DataCache::GetInstance()->GetImage(this->user_->GetProfilePixtureUrl());
    auto&& img2 = img->scaled({80, 80});
    this->user_pix_->setPixmap(QPixmap::fromImage(img2));
}

/*
 *  对话群聊展示面板
 */
ChatGroupBoard::ChatGroupBoard(QWidget* parent)
    : QWidget(parent)
{
    this->window()->setMinimumWidth(390);
    this->window()->setMinimumHeight(720);

    auto img = DataCache::GetInstance()->GetImage("H:/Resources/image/awesomeface.png");
    auto&& img2 = img->scaled({80, 80});

    this->group_pix_ = new QLabel(this);
    this->group_pix_->setPixmap(QPixmap::fromImage(*img));
    {
        this->group_pix_->setFixedSize({80, 80});
    }

    this->group_name_ = new QLabel("name", this);
    this->show_label_ = new QLabel("label", this);
    {
        auto font = this->group_name_->font();
        font.setPointSize(14);
        font.setBold(true);
        this->group_name_->setFont(font);
        this->group_name_->setAlignment(Qt::AlignLeft);
    }
    {
        auto font = this->show_label_->font();
        font.setPointSize(10);
        this->show_label_->setFont(font);
        this->show_label_->setAlignment(Qt::AlignLeft);
    }

    QHBoxLayout* mainLayout = new QHBoxLayout;
    {
        mainLayout->setSpacing(25);

        mainLayout->addWidget(group_pix_);

        QVBoxLayout* subLayout = new QVBoxLayout;
        {
            subLayout->setSpacing(0);

            subLayout->addWidget(group_name_);
            subLayout->addWidget(show_label_);
            subLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
        }
        mainLayout->addLayout(subLayout);
    }
    this->setLayout(mainLayout);
}

void ChatGroupBoard::SetGroup(std::shared_ptr<ChatGroup> group)
{
    this->group_ = group;
    this->Refresh();
}

void ChatGroupBoard::Refresh()
{
    if (this->group_ == nullptr) {
        return;
    }

    this->group_name_->setText(this->group_->GroupName());
    this->show_label_->setText(this->group_->Signature());


    auto img = DataCache::GetInstance()->GetImage(this->group_->GetProfilePixtureUrl());
    auto&& img2 = img->scaled({80, 80});
    this->group_pix_->setPixmap(QPixmap::fromImage(img2));
}

std::shared_ptr<ChatGroup> ChatGroupBoard::Group() const
{
    return group_;
}

/*
 *  对话列表窗口
 */
ChatSessionList::ChatSessionList(QWidget *parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout;
    {
        this->list_widget_ = new QListWidget(this);
        list_widget_->setDragDropMode(QAbstractItemView::InternalMove);
        list_widget_->setResizeMode(QListView::Adjust);
        mainLayout->addWidget(this->list_widget_);

        QObject::connect(this->list_widget_, &QListWidget::itemDoubleClicked,
                         this, &ChatSessionList::slot_ItemDoubleClicked);

        this->list_widget_->setContextMenuPolicy(Qt::CustomContextMenu);
        QObject::connect(this->list_widget_, &QListWidget::customContextMenuRequested, this, &ChatSessionList::slot_ListWidRightClicked);
    }
    this->setLayout(mainLayout);

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


/*
 *  主页面
 */
MainWidget::MainWidget(std::shared_ptr<User> master, QWidget *parent)
    : QWidget{parent}, master_user_(master)
{
    this->resize(ClientSetting::GetInstance()->GetMainWindowSize());
    this->setWindowFlag(Qt::WindowMaximizeButtonHint, false);

    this->setMinimumWidth(390);
    this->setMinimumHeight(720);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    {
        master_board_ = new UserBoard(this);
        master_board_->setMaximumHeight(100);
        mainLayout->addWidget(master_board_);
    }
    {
        auto tab_wid = new QTabWidget(this);
        mainLayout->addWidget(tab_wid);
        {
            user_list_ = new ChatSessionList(this);
            tab_wid->addTab(user_list_, "消息");
        }
        {
            auto sub_tab = new QTabWidget(this);
            {
                this->friend_list_ = new FriendList(this);
                sub_tab->addTab(this->friend_list_, "好友");
            }
            {
                this->class_list_ = new GroupList(this);
                sub_tab->addTab(this->class_list_, "群聊");
            }
            tab_wid->addTab(sub_tab, "联系人");
        }
    }


    this->setLayout(mainLayout);

    this->master_board_->SetUser(master_user_);
}

void MainWidget::closeEvent(QCloseEvent *event)
{
    auto temp = QMessageBox::information(this, "确认", "是否关闭?", QMessageBox::Yes | QMessageBox::No);
    if (temp == QMessageBox::Yes)
    {
        qDebug() << "main window close";
        WindowManager::GetInstance()->slot_DestroyAllChatSession();
        event->accept();
    }
    else
    {
        //忽略了 要关闭这个窗口的事件.当前窗口就不会被关闭.
        event->ignore();
    }
}
