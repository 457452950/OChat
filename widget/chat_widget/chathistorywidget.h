#ifndef CHATHISTORYWIDGET_H
#define CHATHISTORYWIDGET_H

#include <QLabel>
#include <QListWidget>
#include <QTextLayout>
#include <QWidget>

#include "../../data_structure/datasructures.h"

/*
 *  对话记录
 */
class ChatEntryWidget : public QWidget {
    Q_OBJECT
public:
    explicit ChatEntryWidget(QListWidgetItem* item, QWidget* parent);

    void SetSender(std::shared_ptr<User> user, bool self);

    void SetText(QString text, QDateTime time);

    int GetHight();

    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    QListWidgetItem* item_;

    bool self_;

    QLabel* pic_;
    QLabel* message_;
    QLabel* extra_;

    static int main_margin;
    static int text_margin;
    static int text_rounding;
    static int header_pix_size;
};

inline int ChatEntryWidget::main_margin = 5;
inline int ChatEntryWidget::text_margin = 15;
inline int ChatEntryWidget::text_rounding = 5;
inline int ChatEntryWidget::header_pix_size = 42;


/*
 *  对话展示框
 */
class ChatHistoryWidget : public QWidget {
    Q_OBJECT
public:
    explicit ChatHistoryWidget(QWidget* parent);

    void AddHistory(std::shared_ptr<ChatHistory> history);
    void AppendHistory(std::shared_ptr<ChatHistory> history);

private:
    QListWidget* chat_entrys_;

    struct Entry{
        std::shared_ptr<ChatHistory> history;
        QListWidgetItem* item;
    };
    QVector<Entry> entrys_;
};



#endif // CHATHISTORYWIDGET_H
