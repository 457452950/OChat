#include "mainwidget.h"

#include <QPixmap>
#include <QImage>
#include <QBoxLayout>

#include "../config/clientconfig.h"


UserBoard::UserBoard(QWidget* parent)
    : QWidget(parent)
{
    QImage img;
    auto ok = img.load("H:\\Resources\\paimeng.jpg");
    if (!ok) {
        qFatal() << "load image err";
        return;
    } else {
        qDebug() << "read ok";
    }
    img = img.scaled({80, 80});

    this->user_pix_ = new QLabel(this);
    this->user_pix_->setPixmap(QPixmap::fromImage(img));

    this->user_name_ = new QLabel("name", this);
    this->user_signature_ = new QLabel("signature", this);
    {
        auto font = this->user_name_->font();
        font.setPointSize(14);
        font.setBold(true);
        this->user_name_->setFont(font);
    }
    {
        auto font = this->user_signature_->font();
        font.setPointSize(10);
        this->user_signature_->setFont(font);
    }

    QHBoxLayout* mainLayout = new QHBoxLayout;
    {
        mainLayout->addWidget(user_pix_);

        QVBoxLayout* subLayout = new QVBoxLayout;
        {
            subLayout->addWidget(user_name_);
            subLayout->addWidget(user_signature_);
            subLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
        }
        mainLayout->addLayout(subLayout);
    }
    this->setLayout(mainLayout);
}

void UserBoard::SetName(QString name)
{
    this->user_name_->setText(name);
}

void UserBoard::SetSignature(QString signature)
{
    this->user_signature_->setText(signature);
}

ChatSessionList::ChatSessionList(QWidget *parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout;
    {
        this->list_widget_ = new QListWidget(this);
        list_widget_->setDragDropMode(QAbstractItemView::InternalMove);
        list_widget_->setResizeMode(QListView::Adjust);
        mainLayout->addWidget(this->list_widget_);
    }
    this->setLayout(mainLayout);

    {
        this->AddUser("1", "aaaaa");
        this->AddUser("2", "bbbb");
        this->AddUser("3", "ccc");
        this->AddUser("4", "dd");
        this->AddUser("1", "aaaaa");
        this->AddUser("2", "bbbb");
        this->AddUser("3", "ccc");
        this->AddUser("4", "dd");
        this->AddUser("1", "aaaaa");
        this->AddUser("2", "bbbb");
        this->AddUser("3", "ccc");
        this->AddUser("4", "dd");
    }
}

void ChatSessionList::AddUser(QString name, QString signature)
{
    UserBoard* board = new UserBoard(this);
    board->SetName(name);
    board->SetSignature(signature);

    QListWidgetItem* item = new QListWidgetItem;
    item->setSizeHint({0, 80});

    this->list_widget_->addItem(item);
    this->list_widget_->setItemWidget(item, board);
}


MainWidget::MainWidget(QWidget *parent)
    : QWidget{parent}
{
    this->resize(ClientConfig::GetInstance()->GetMainWindowSize());
    this->setWindowFlag(Qt::WindowMaximizeButtonHint, false);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    {
        user_board_ = new UserBoard(this);
        user_board_->setMaximumHeight(100);
        mainLayout->addWidget(user_board_);
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

    this->AddUser("我的好友", "asd", "asda");
    this->AddUser("我的好友", "asd", "asda");
    this->AddUser("我的好友", "asd", "asda");
}

void UserList::AddUser(QString party, QString name, QString signature)
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
        board->SetName(name);
        board->SetSignature(signature);
        this->root_->setItemWidget(n, 0, board);
    }
}
