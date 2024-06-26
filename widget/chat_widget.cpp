#include "chat_widget.h"

#include <QBoxLayout>
#include <QPainter>
#include <QPalette>
#include <QSplitter>

#include "backend/backend.h"
#include "common/config/client_setting.h"
#include "widget/wrapper.h"
#include "window_manager.h"


/* 聊天对话窗 */
ChatWidget::ChatWidget(QString group_uid, QWidget *parent) : QWidget{parent} {
    ChangeManager.Register(this, {group_uid});

    this->initLayout();

    auto room = Backend::GetInstance()->GetRoom(group_uid);
    if(room == nullptr) {
        this->Refresh("待刷新");
    } else {
        this->Refresh(room->name);
    }
}

ChatWidget::~ChatWidget() {
    ChangeManager.UnRegister(this);
    input_->SetListeaner(nullptr);
}

void ChatWidget::Refresh(const QString &group_name) { this->setWindowTitle(group_name); }

void ChatWidget::initLayout() {
    this->resize(SETTING->ChatWindowSize);
    this->setMinimumSize(SETTING->ChatWindowMinimumSize);


    // 设置背景色
    auto pal = this->palette();
    pal.setColor(QPalette::Window, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);


    const int margin = 0;

    QHBoxLayout *main_layout = new QHBoxLayout(this);
    main_layout->setContentsMargins(QMargins(margin, margin, margin, margin));
    main_layout->setSpacing(0);
    {
        QVBoxLayout *session = new QVBoxLayout();
        session->setSpacing(0);
        {
            QHBoxLayout *features = new QHBoxLayout();
            {
                QSpacerItem *space_item = new QSpacerItem(9999, 0, QSizePolicy::Maximum, QSizePolicy::Minimum);
                features->addSpacerItem(space_item);

                show_history_ = new QPushButton("history", this);
                features->addWidget(show_history_);

                more_ = new QPushButton("更多", this);
                features->addWidget(more_);
            }
            session->addLayout(features);

            QSplitter *splitter = new QSplitter(Qt::Vertical, this);
            {
                history_ = new ChatHistoryWidget(this);
                splitter->addWidget(history_);

                input_ = new InputWidget(this);
                input_->SetListeaner(this);
                splitter->addWidget(input_);

                splitter->setStretchFactor(0, 1);
                splitter->setStretchFactor(1, 0);
            }
            session->addWidget(splitter);
        }
        main_layout->addLayout(session);

        // note : more chat history
        wid_ = new QWidget(this);
        wid_->setFixedWidth(200);
        wid_->hide();
        main_layout->addWidget(wid_);
    }
    this->setLayout(main_layout);

    QObject::connect(show_history_, &QPushButton::released, this, &ChatWidget::slot_BtnShowHistoryReleased);
}

void ChatWidget::slot_BtnShowHistoryReleased() {
    auto current_size = this->size();
    if(this->wid_->isHidden()) {
        this->resize(current_size.width() + 200, current_size.height());
        this->wid_->setHidden(false);
    } else {
        this->resize(current_size.width() - 200, current_size.height());
        this->wid_->setHidden(true);
    }
}

void ChatWidget::UserInput(const QString &text) { qDebug() << "input : " << text; }
