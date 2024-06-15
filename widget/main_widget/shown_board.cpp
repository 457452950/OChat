#include "shown_board.h"

#include <QBoxLayout>

#include <lazybox/Assert.hpp>

#include "window_manager.h"
#include "cache/data_cache.h"
#include "common/config/client_setting.h"


/*
 *  用户展示面板
 */
ShownBoard::ShownBoard(QWidget *parent) : QWidget(parent) {
    auto img = DataCache::GetInstance()->GetImage("H:/Resources/image/awesomeface.png");

    this->pix_ = new QLabel(this);
    auto s     = std::min<int>(img->width(), img->height());
    auto image = img->scaled({s, s}, Qt::KeepAspectRatioByExpanding);
    this->pix_->setPixmap(QPixmap::fromImage(image));
    this->pix_->setScaledContents(true);
    {
        // this->user_pix_->setFixedSize({80, 80});
    }

    this->name_       = new QLabel("name", this);
    this->show_label_ = new QLabel("label", this);
    {
        auto font = this->name_->font();
        font.setPointSize(14);
        font.setBold(true);
        this->name_->setFont(font);
        this->name_->setAlignment(Qt::AlignLeft);
    }
    {
        auto font = this->show_label_->font();
        font.setPointSize(10);
        this->show_label_->setFont(font);
        this->show_label_->setAlignment(Qt::AlignLeft);
    }

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setContentsMargins(5, 5, 5, 5);
    {
        mainLayout->setSpacing(25);

        mainLayout->addWidget(pix_);

        QVBoxLayout *subLayout = new QVBoxLayout;
        {
            subLayout->setSpacing(0);

            subLayout->addWidget(name_);
            subLayout->addWidget(show_label_);
            subLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
        }
        mainLayout->addLayout(subLayout);

        mainLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    }
    this->setLayout(mainLayout);
}

ShownBoard::~ShownBoard() { ChangeManager.UnRegister(this); }

void ShownBoard::SetUser(const QString &uid) {
    ChangeManager.Register(this, {uid});
    auto user = Backend::GetInstance()->GetUser(uid);
    Assert(user, "user not found {}", uid.toStdString());
    this->Refresh(*user);
}

void ShownBoard::SetRoom(const QString &uid) {
    ChangeManager.Register(this, {uid});
    auto room = Backend::GetInstance()->GetRoom(uid);
    Assert(room, "user not found {}", uid.toStdString());
    this->Refresh(*room);
}

void ShownBoard::Refresh(const User &user) {
    this->name_->setText(user.GetName());
    this->show_label_->setText(user.GetSignature());

    auto img = DataCache::GetInstance()->GetImage(user.GetProfilePixtureUrl());
    if(img == nullptr) {
        img = DataCache::GetInstance()->GetImage(SETTING->UserNoneImage);
    }

    auto   s    = std::min<int>(img->width(), img->height());
    auto &&img2 = img->scaled({s, s}, Qt::KeepAspectRatioByExpanding);
    this->pix_->setPixmap(QPixmap::fromImage(img2));
}

void ShownBoard::Refresh(const ChatRoom &room) {
    this->name_->setText(room.GetName());
    this->show_label_->setText(room.GetSignature());

    auto   img  = DataCache::GetInstance()->GetImage(room.GetProfilePixtureUrl());
    auto   s    = std::min<int>(img->width(), img->height());
    auto &&img2 = img->scaled({s, s}, Qt::KeepAspectRatioByExpanding);
    this->pix_->setPixmap(QPixmap::fromImage(img2));
}


void ShownBoard::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    auto s = std::min<int>(this->pix_->width(), this->pix_->height());
    this->pix_->setFixedSize(QSize{s, s});
}
