#include "inputwidget.h"

#include <QBoxLayout>
#include <QSpacerItem>


/* 输入框 */
InputWidget::InputWidget(QWidget *parent)
    : QWidget(parent)
{

    QVBoxLayout* main_layout = new QVBoxLayout(this);
    main_layout->setContentsMargins(0, 0, 0 ,0);
    main_layout->setSpacing(0);
    {
        // 功能按钮
        QHBoxLayout* buttons_line = new QHBoxLayout();
        buttons_line->setSpacing(0);
        {
            // 插入图片
            image_ = new QPushButton("image", this);
            buttons_line->addWidget(image_);

            // 更多
            more_ = new QPushButton("...", this);
            buttons_line->addWidget(more_);

            QSpacerItem* space_item = new QSpacerItem(9999, 0, QSizePolicy::Maximum, QSizePolicy::Minimum);
            buttons_line->addSpacerItem(space_item);
        }
        main_layout->addLayout(buttons_line);

        {
            // 输入框
            input_ = new QTextEdit(this);
            input_->setFrameShape(QFrame::NoFrame);
            auto font = input_->font();
            font.setPointSize(16);
            input_->setFont(font);
            main_layout->addWidget(input_);
        }


        buttons_line = new QHBoxLayout();
        buttons_line->setSpacing(0);
        {
            // 发送按钮
            QSpacerItem* space_item = new QSpacerItem(9999, 0, QSizePolicy::Maximum, QSizePolicy::Minimum);
            buttons_line->addSpacerItem(space_item);

            send_ = new QPushButton("send", this);
            buttons_line->addWidget(send_);
        }
        main_layout->addLayout(buttons_line);
    }
    this->setLayout(main_layout);
    this->resize(this->size().width(), 210);

    // connect
    {
        QObject::connect(this->send_, &QPushButton::released, this, &InputWidget::slot_BtnSendReleased);
    }
}

void InputWidget::SetListeaner(Listeaner *new_listeaner)
{
    listeaner_ = new_listeaner;
}

void InputWidget::slot_BtnSendReleased()
{
    auto text = this->input_->toPlainText();
    this->input_->clear();

    if (listeaner_ && !text.isEmpty()) {
        listeaner_->UserInput(text);
    }
}
