#ifndef CHATHISTORYWIDGET_H
#define CHATHISTORYWIDGET_H

#include <QListWidget>
#include <QWidget>



/*
 *  对话记录
 */
class ChatEntryWidget : public QWidget {
    Q_OBJECT
public:
    explicit ChatEntryWidget(QWidget* parent);

    void paintEvent(QPaintEvent* event) override;

private:

};

/*
 *  对话展示框
 */
class ChatHistoryWidget : public QWidget {
    Q_OBJECT
public:
    explicit ChatHistoryWidget(QWidget* parent);

private:
    QListWidget* chat_entrys_;
};



#endif // CHATHISTORYWIDGET_H
