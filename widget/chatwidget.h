#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>


#include "../data_structure/datasructures.h"

#include "chat_widget/chathistorywidget.h"
#include "chat_widget/inputwidget.h"



/* 聊天对话窗 */
class ChatWidget : public QWidget, public InputWidget::Listeaner
{
    Q_OBJECT
public:
    explicit ChatWidget(QString group_uid, QWidget *parent = nullptr);
    explicit ChatWidget(std::shared_ptr<ChatGroup> group, QWidget *parent = nullptr);
    ~ChatWidget() { input_->SetListeaner(nullptr); }

    void Refresh();

signals:

private:
    void initLayout();
    void slot_BtnShowHistoryReleased();

    void UserInput(const QString& text) override;

private:
    /* layout */
    QPushButton* show_history_;
    QPushButton* more_;

    ChatHistoryWidget* history_;

    InputWidget* input_;

    QWidget* wid_;

    /* data */
    std::shared_ptr<ChatGroup> group_;
};

#endif // CHATWIDGET_H
