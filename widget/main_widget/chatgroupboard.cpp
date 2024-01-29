#include "chatgroupboard.h"

#include "../../cache/datacache.h"

#include <QBoxLayout>

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
    mainLayout->setContentsMargins(0, 0,0,0);
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

