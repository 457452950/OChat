#include "chatwidget.h"

#include <QBoxLayout>
#include <QPainter>
#include <QPalette>
#include <QSplitter>

#include "../backend/backend.h"



/* 聊天对话窗 */
ChatWidget::ChatWidget(QString group_uid, QWidget *parent)
    : QWidget{parent}
{
    this->group_ = Backend::GetInstance()->GetGroupFromUid(group_uid);

    this->initLayout();
}

ChatWidget::ChatWidget(std::shared_ptr<ChatGroup> group, QWidget *parent)
    : QWidget(parent), group_(group)
{
    this->initLayout();
}

void ChatWidget::Refresh()
{
    Q_ASSERT(this->group_);
    
    this->setWindowTitle(this->group_->Name());
}

void ChatWidget::initLayout()
{
    this->resize({800, 600});
    this->setMinimumWidth(600);
    this->setMinimumHeight(450);


    // 设置背景色
    auto pal = this->palette();
    pal.setColor(QPalette::Window, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);


    const int margin = 0;

    QHBoxLayout* main_layout = new QHBoxLayout(this);
    main_layout->setContentsMargins(QMargins(margin, margin, margin, margin));
    main_layout->setSpacing(0);
    {
        QVBoxLayout* session = new QVBoxLayout();
        session->setSpacing(0);
        {
            QHBoxLayout* features = new QHBoxLayout();
            {
                QSpacerItem* space_item = new QSpacerItem(9999, 0, QSizePolicy::Maximum, QSizePolicy::Minimum);
                features->addSpacerItem(space_item);

                show_history_ = new QPushButton("history", this);
                features->addWidget(show_history_);

                more_ = new QPushButton("更多", this);
                features->addWidget(more_);
            }
            session->addLayout(features);

            QSplitter* splitter = new QSplitter(Qt::Vertical, this);

            history_ = new ChatHistoryWidget(this);
            splitter->addWidget(history_);

            input_ = new InputWidget(this);
            input_->SetListeaner(this);
            splitter->addWidget(input_);

            splitter->setStretchFactor(0, 1);
            splitter->setStretchFactor(1, 0);
            session->addWidget(splitter);
        }
        main_layout->addLayout(session);

        wid_ = new QWidget(this);
        wid_->setFixedWidth(200);
        wid_->hide();
        main_layout->addWidget(wid_);
    }
    this->setLayout(main_layout);

    QObject::connect(show_history_, &QPushButton::released, this, &ChatWidget::slot_BtnShowHistoryReleased);

    this->Refresh();
}

void ChatWidget::slot_BtnShowHistoryReleased()
{
    auto current_size = this->size();
    if (this->wid_->isHidden()) {
        this->resize(current_size.width() + 200, current_size.height());
        this->wid_->setHidden(false);
    } else {
        this->resize(current_size.width() - 200, current_size.height());
        this->wid_->setHidden(true);
    }
}

void ChatWidget::UserInput(const QString &text)
{
    qDebug() << "input : " << text;
}


