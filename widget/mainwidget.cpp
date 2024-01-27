#include "mainwidget.h"

#include <QPixmap>
#include <QImage>
#include <QBoxLayout>
#include <QMenu>

#include "../config/clientsetting.h"
#include "../cache/datacache.h"

UserBoard::UserBoard(QWidget* parent)
    : QWidget(parent)
{
    this->window()->setMinimumWidth(390);
    this->window()->setMinimumHeight(720);

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
    this->Update();
}

void UserBoard::Update()
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
        auto user1 = std::make_shared<User>();
        user1->SetUserName("1");
        user1->SetSignature("aaaa");
        user1->SetProfilePixtureUrl("H:/Resources/a.png");

        auto user2 = std::make_shared<User>();
        user2->SetUserName("2");
        user2->SetSignature("bbb");
        user2->SetProfilePixtureUrl("H:/Resources/m2.png");

        auto user3 = std::make_shared<User>();
        user3->SetUserName("3");
        user3->SetSignature("cc");
        user3->SetProfilePixtureUrl("H:/Resources/stand.png");

        auto user4 = std::make_shared<User>();
        user4->SetUserName("4");
        user4->SetSignature("d");
        user4->SetProfilePixtureUrl("H:/Resources/stuff.jpg");

        this->AddUser(user1);
        this->AddUser(user2);
        this->AddUser(user3);
        this->AddUser(user4);
        this->AddUser(user1);
        this->AddUser(user2);
        this->AddUser(user3);
        this->AddUser(user4);
        this->AddUser(user1);
        this->AddUser(user2);
        this->AddUser(user3);
        this->AddUser(user4);
    }
#endif
}

void ChatSessionList::AddUser(std::shared_ptr<User> user)
{
    UserBoard* board = new UserBoard(this);
    board->SetUser(user);

    QListWidgetItem* item = new QListWidgetItem;
    item->setSizeHint({0, 90});

    this->list_widget_->addItem(item);
    this->list_widget_->setItemWidget(item, board);
}

void ChatSessionList::slot_ItemDoubleClicked(QListWidgetItem *item)
{
    auto index = this->list_widget_->indexFromItem(item);

    qDebug() << "item double clicked " << item->text() << " " << index.row();
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


MainWidget::MainWidget(std::shared_ptr<User> master, QWidget *parent)
    : QWidget{parent}, master_user_(master)
{
    this->resize(ClientSetting::GetInstance()->GetMainWindowSize());
    this->setWindowFlag(Qt::WindowMaximizeButtonHint, false);

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
                this->friend_list_ = new UserList(this);
                sub_tab->addTab(this->friend_list_, "好友");
            }
            {
                this->class_list_ = new UserList(this);
                sub_tab->addTab(this->class_list_, "群聊");
            }
            tab_wid->addTab(sub_tab, "联系人");
        }
    }


    this->setLayout(mainLayout);

    this->master_board_->SetUser(master_user_);
}

UserList::UserList(QWidget *parent)
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
        auto user = std::make_shared<User>();
        user->SetUserName("asd");
        user->SetSignature("asda");
        user->SetProfilePixtureUrl("H:/Resources/image/snake.jpg");

        this->AddUser("我的好友", user);
        this->AddUser("我的好友", user);
        this->AddUser("我的好友", user);
    }
#endif
}

void UserList::AddUser(QString party, std::shared_ptr<User> user)
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
