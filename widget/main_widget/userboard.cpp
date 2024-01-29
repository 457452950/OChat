#include "userboard.h"

#include "../../cache/datacache.h"

#include <QBoxLayout>

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
    mainLayout->setContentsMargins(0, 0, 0, 0);
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
