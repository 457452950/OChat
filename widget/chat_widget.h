#ifndef OCHAT__WIDGET__CHAT_WIDGET_H
#define OCHAT__WIDGET__CHAT_WIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>


#include "widget/wrapper.h"

#include "chat_widget/chat_history_widget.h"
#include "chat_widget/input_widget.h"


/* 聊天对话窗 */
class ChatWidget : public QWidget, public InputWidget::Listeaner, public ObjectChangeList::Listener {
    Q_OBJECT
public:
    explicit ChatWidget(QString group_uid, QWidget *parent = nullptr);
    ~ChatWidget();

    void Refresh(const QString &group_name);

signals:

private:
    void initLayout();
    void slot_BtnShowHistoryReleased();

    void UserInput(const QString &text) override;

private:
    /* layout */
    QPushButton *show_history_;
    QPushButton *more_;

    ChatHistoryWidget *history_;

    InputWidget *input_;

    QWidget *wid_;
};

#endif // OCHAT__WIDGET__CHAT_WIDGET_H
