#include "usergroupboard.h"

#include "../../cache/datacache.h"

#include <QBoxLayout>

/*
 *  用户展示面板
 */
UserGroupBoard::UserGroupBoard(QWidget* parent)
    : QWidget(parent)
{
    auto img = DataCache::GetInstance()->GetImage("H:/Resources/image/awesomeface.png");
    
    this->pix_ = new QLabel(this);
    auto s = std::min(img->width(), img->height());
    auto image = img->scaled({s, s}, Qt::KeepAspectRatioByExpanding);
    this->pix_->setPixmap(QPixmap::fromImage(image));
    this->pix_->setScaledContents(true);
    {
        // this->user_pix_->setFixedSize({80, 80});
    }

    this->name_ = new QLabel("name", this);
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

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->setContentsMargins(5, 5, 5, 5);
    {
        mainLayout->setSpacing(25);
        
        mainLayout->addWidget(pix_);

        QVBoxLayout* subLayout = new QVBoxLayout;
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

void UserGroupBoard::SetUser(std::shared_ptr<UIUser> user)
{
    this->user_ = user;
    this->group_.reset();
    this->Refresh();
}

void UserGroupBoard::SetGroup(std::shared_ptr<ChatGroup> group)
{
    this->user_.reset();
    this->group_ = group;
    this->Refresh();
}

void UserGroupBoard::Refresh()
{
    if (this->user_) {
        // user
        this->name_->setText(this->user_->Name());
        this->show_label_->setText(this->user_->Signature());

        auto img = DataCache::GetInstance()->GetImage(this->user_->GetProfilePixtureUrl());
        auto s = std::min(img->width(), img->height());
        auto&& img2 = img->scaled({s, s}, Qt::KeepAspectRatioByExpanding);
        this->pix_->setPixmap(QPixmap::fromImage(img2));
    } else {
        // group
        this->name_->setText(this->group_->Name());
        this->show_label_->setText(this->group_->Signature());

        auto img = DataCache::GetInstance()->GetImage(this->group_->GetProfilePixtureUrl());
        auto s = std::min(img->width(), img->height());
        auto&& img2 = img->scaled({s, s}, Qt::KeepAspectRatioByExpanding);
        this->pix_->setPixmap(QPixmap::fromImage(img2));
    }
}

void UserGroupBoard::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    auto s = std::min(this->pix_->width(), this->pix_->height());
    this->pix_->setFixedSize(QSize{s, s});
}
