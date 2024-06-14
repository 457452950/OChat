#include "chat_history_widget.h"

#include <QBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include <QScrollBar>

#include "backend/backend.h"
#include "cache/data_cache.h"

/*
 *  对话记录
 */
ChatEntryWidget::ChatEntryWidget(QListWidgetItem *item, QWidget *parent) : QWidget(parent), item_(item) {
    pic_ = new QLabel(this);

    message_ = new QLabel(this);
    message_->setWordWrap(true);
    message_->hide();

    extra_ = new QLabel(this);
}

void ChatEntryWidget::SetSender(const User &user) {
    bool is_self = Backend::GetInstance()->self_.GetUid() == user.GetUid();

    auto img   = DataCache::GetInstance()->GetImage(user.GetProfilePixtureUrl());
    auto s     = std::min<int>(img->width(), img->height());
    auto image = img->scaled({s, s}, Qt::KeepAspectRatioByExpanding);
    this->pic_->setPixmap(QPixmap::fromImage(image));
    this->pic_->setScaledContents(true);
    this->pic_->setFixedSize(header_pix_size, header_pix_size);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(main_margin, main_margin, main_margin, main_margin);

    if(is_self) {
        extra_->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        mainLayout->addWidget(extra_);
        mainLayout->addWidget(message_);
        mainLayout->addWidget(pic_);
    } else {
        mainLayout->addWidget(pic_);
        mainLayout->addWidget(message_);
        mainLayout->addWidget(extra_);
        extra_->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    }

    this->setLayout(mainLayout);
}

void ChatEntryWidget::SetText(QString text, QDateTime time) {
    message_->setText(text);
    message_->setTextInteractionFlags(Qt::TextSelectableByMouse);
    auto font = message_->font();
    font.setPointSize(13);
    message_->setFont(font);
    message_->show();
    message_->setMargin(text_margin);

    extra_->setText(time.toString("yy.M.d h:m:s.z"));
}

void ChatEntryWidget::paintEvent(QPaintEvent *event) {
    // QWidget::paintEvent(event);

    QPainter painter(this);
    QPen     pen;
    pen.setColor(Qt::black);
    painter.setPen(pen);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::green);

    // qDebug() << "paint event";

    auto         t    = text_margin - text_rounding;
    auto       &&rect = QRect(message_->pos() + QPoint{t, t}, message_->size() - QSize{2 * t, 2 * t});
    QPainterPath path;
    path.addRoundedRect(rect, text_rounding, text_rounding);
    painter.drawPath(path);
    painter.fillPath(path, brush);

    painter.drawRect(QRect(pic_->pos(), pic_->size()));

    // painter.drawRect(QRect(extra_->pos(), extra_->size()));
}

void ChatEntryWidget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    if(event->oldSize().width() == event->size().width()) {
        return;
    }

    // qDebug() << "resize event" << event->oldSize() << event->size() << message_->sizeHint() << message_->sizePolicy()
    // << message_->heightForWidth(event->size().width() - 32);

    auto label_height = message_->heightForWidth(event->size().width() - header_pix_size - 2 * main_margin);
    auto wid_height   = std::max<int>(label_height, pic_->height()) + 2 * main_margin;

    auto size = event->size();
    size.setHeight(wid_height);
    this->resize(size);

    size = {1, wid_height};
    item_->setSizeHint(size);
}


/*
 *  对话展示框
 */
ChatHistoryWidget::ChatHistoryWidget(QWidget *parent) : QWidget(parent) {
    QHBoxLayout *main_layout = new QHBoxLayout(this);
    main_layout->setContentsMargins(0, 0, 0, 0);
    {
        chat_entrys_widget_ = new QListWidget(this);
        chat_entrys_widget_->setFrameShape(QFrame::NoFrame);
        main_layout->addWidget(chat_entrys_widget_);
    }
    this->setLayout(main_layout);

    chat_entrys_widget_->setSelectionMode(QAbstractItemView::NoSelection);
    chat_entrys_widget_->setUniformItemSizes(false);
    chat_entrys_widget_->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    chat_entrys_widget_->verticalScrollBar()->setSingleStep(10);

#ifdef QT_DEBUG
    {
        // auto history = std::make_shared<ChatEntry>();
        //         history->SetFromTo("10000", "10001");
        //         history->SetMessageText("啊实打实大苏打撒撒入发放");
        //         this->AddHistory(history);

        //         QString msg_text =
        //                 R"(class ChatEntryWidget : public QWidget {
        // public:
        //     explicit ChatEntryWidget(QListWidgetItem* item, QWidget* parent);

        //     void SetSender(std::shared_ptr<User> user, bool self);

        //     void SetText(QString text);

        //     int GetHight();

        //     void paintEvent(QPaintEvent* event) override;
        //     void resizeEvent(QResizeEvent* event) override;

        // private:
        //     QListWidgetItem* item_;

        //     bool self_;
        //     QLabel* pic_;
        //     QLabel* text_;
        // };)";

        //         history = std::make_shared<ChatEntry>();
        //         history->SetFromTo("10001", "10000");
        //         history->SetMessageText(msg_text);
        //         this->AddHistory(history);

        //         history = std::make_shared<ChatEntry>();
        //         history->SetFromTo("10001", "10000");
        //         history->SetMessageText(msg_text);
        //         this->AddHistory(history);

        //         history = std::make_shared<ChatEntry>();
        //         history->SetFromTo("10001", "10000");
        //         history->SetMessageText(msg_text);
        //         this->AddHistory(history);
    }
#endif
}

void ChatHistoryWidget::AddHistory(std::shared_ptr<ChatEntry> history) {
    auto item = new QListWidgetItem;
    // item->setSizeHint(QSize(1, 80));
    auto wid  = new ChatEntryWidget(item, this);

    int index = -1;
    for(int i = 0; i < entrys_.size(); ++i) {
        if(entrys_[i].history == history) {
            return;
        }
        if(entrys_[i].history->Date() > history->Date()) {
            break;
        }
        index = i;
    }

    index += 1;
    entrys_.insert(index, {history, item});

    this->chat_entrys_widget_->insertItem(index, item);
    this->chat_entrys_widget_->setItemWidget(item, wid);

    auto uid = history->From();
    wid->SetSender(uid);
    wid->SetText(history->Context().text, QDateTime::fromMSecsSinceEpoch((history->Date())));
    qDebug() << QDateTime::fromMSecsSinceEpoch((history->Date()));
}
