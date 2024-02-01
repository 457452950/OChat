#include "chathistorywidget.h"

#include <QBoxLayout>
#include <QPainter>
#include <QPainterPath>

#include "../../backend/backend.h"
#include "../../cache/datacache.h"

/*
 *  对话记录
 */
ChatEntryWidget::ChatEntryWidget(QListWidgetItem* item, QWidget *parent)
    : QWidget(parent), item_(item){
    pic_ = new QLabel(this);

    text_ = new QLabel(this);
    text_->setWordWrap(true);
    text_->hide();
}

void ChatEntryWidget::SetSender(std::shared_ptr<User> user, bool self)
{
    auto img = DataCache::GetInstance()->GetImage(user->GetProfilePixtureUrl());
    auto s = std::min(img->width(), img->height());
    auto image = img->scaled({s, s}, Qt::KeepAspectRatioByExpanding);
    this->pic_->setPixmap(QPixmap::fromImage(image));
    this->pic_->setScaledContents(true);
    this->pic_->setFixedSize(header_pix_size, header_pix_size);

    self_ = self;

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(main_margin, main_margin, main_margin, main_margin);

    if (self_) {
        mainLayout->addWidget(text_);
        mainLayout->addWidget(pic_);
    } else {
        mainLayout->addWidget(pic_);
        mainLayout->addWidget(text_);
    }

    this->setLayout(mainLayout);
}

void ChatEntryWidget::SetText(QString text)
{
    text_->setText(text);
    text_->setTextInteractionFlags(Qt::TextSelectableByMouse);
    auto font = text_->font();
    font.setPointSize(13);
    text_->setFont(font);
    text_->show();
    text_->setMargin(text_margin);
}

void ChatEntryWidget::paintEvent(QPaintEvent *event)
{
    // QWidget::paintEvent(event);

    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::black);
    painter.setPen(pen);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::green);

    // qDebug() << "paint event";

    auto t = text_margin - text_rounding;
    auto&& rect = QRect(text_->pos() + QPoint{t, t}, text_->size() - QSize{2 * t, 2 * t});
    QPainterPath path;
    path.addRoundedRect(rect, text_rounding, text_rounding);
    painter.drawPath(path);
    painter.fillPath(path, brush);

    painter.drawRect(QRect(pic_->pos(), pic_->size()));
}

void ChatEntryWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    if (event->oldSize().width() == event->size().width()) {
        return;
    }

    // qDebug() << "resize event" << event->oldSize() << event->size() << text_->sizeHint() << text_->sizePolicy() << text_->heightForWidth(event->size().width() - 32);

    auto label_height = text_->heightForWidth(event->size().width() - header_pix_size - 2 * main_margin);
    auto wid_height = std::max(label_height, pic_->height()) + 2 * main_margin;

    auto size = event->size();
    size.setHeight(wid_height);
    this->resize(size);

    size = {1, wid_height};
    item_->setSizeHint(size);
}


/*
 *  对话展示框
 */
ChatHistoryWidget::ChatHistoryWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout* main_layout = new QHBoxLayout(this);
    main_layout->setContentsMargins(0, 0, 0 ,0);
    {
        chat_entrys_ = new QListWidget(this);
        chat_entrys_->setFrameShape(QFrame::NoFrame);
        main_layout->addWidget(chat_entrys_);
    }
    this->setLayout(main_layout);

    chat_entrys_->setSelectionMode(QAbstractItemView::NoSelection);
    chat_entrys_->setUniformItemSizes(false);

#ifdef QT_DEBUG
    {
        Q_ASSERT(User::CheckUserUid("10000") == true);
        Q_ASSERT(User::CheckUserUid("1000") == false);

        auto history = std::make_shared<ChatHistory>();
        history->SetFromTo("10000", "10001");
        history->SetMessageText("啊实打实大苏打撒撒入发放");
        this->AddHistory(history);

        history = std::make_shared<ChatHistory>();
        history->SetFromTo("10001", "10000");
        history->SetMessageText(
R"(class ChatEntryWidget : public QWidget {
public:
    explicit ChatEntryWidget(QListWidgetItem* item, QWidget* parent);

    void SetSender(std::shared_ptr<User> user, bool self);

    void SetText(QString text);

    int GetHight();

    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    QListWidgetItem* item_;

    bool self_;
    QLabel* pic_;
    QLabel* text_;
};)"        );
        this->AddHistory(history);
    }
#endif
}

void ChatHistoryWidget::AddHistory(std::shared_ptr<ChatHistory> history)
{
    auto item = new QListWidgetItem;
    // item->setSizeHint(QSize(1, 80));
    auto wid = new ChatEntryWidget(item, this);

    int index = -1;
    for (int i = 0; i < entrys_.size(); ++i) {
        if (entrys_[i].history->Date() > history->Date()) {
            break;
        }
        index = i;
    }

    index += 1;
    entrys_.insert(index, {history, item});

    this->chat_entrys_->insertItem(index, item);
    this->chat_entrys_->setItemWidget(item, wid);

    auto uid = history->From();
    wid->SetSender(Backend::GetInstance()->GetUserFromUid(uid), uid == Backend::GetInstance()->SelfUser()->Uid());
    wid->SetText(history->MessageText());
    qDebug() << history->Date();
}
