#include "chathistorywidget.h"

#include <QBoxLayout>
#include <QPainter>


/*
 *  对话记录
 */
ChatEntryWidget::ChatEntryWidget(QWidget *parent)
    : QWidget(parent){

}

void ChatEntryWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.drawRect(QRect(0, 0, this->width() - 1, this->height() - 1));
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
}
