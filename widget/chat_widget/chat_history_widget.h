#ifndef OCHAT__WIDGET_CHAT_WIDGET__CHAT_HISTORY_WIDGET_H
#define OCHAT__WIDGET_CHAT_WIDGET__CHAT_HISTORY_WIDGET_H

#include <QLabel>
#include <QListWidget>
#include <QTextLayout>
#include <QWidget>
#include <QMatrix4x4>

#include <lazybox/Assert.hpp>

#include "widget/wrapper.h"

/*
 *  对话记录
 */
class ChatEntryWidget : public QWidget, public ObjectChangeList::Listener {
    Q_OBJECT
public:
    explicit ChatEntryWidget(QListWidgetItem *item, QWidget *parent);

    void SetSender(const User &user);
    void SetSender(const QString &uid) {
        auto user = Backend::GetInstance()->GetUser(uid);
        Assert(user);
        this->SetSender(*user);
    }

    void SetText(QString text, QDateTime time);

    int GetHight();

    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void OnUserUpdate(const User &user) override { this->SetSender(user); }


private:
    QListWidgetItem *item_;

    bool self_;

    QLabel *pic_;
    QLabel *message_;
    QLabel *extra_;

    static int main_margin;
    static int text_margin;
    static int text_rounding;
    static int header_pix_size;
};

inline int ChatEntryWidget::main_margin     = 5;
inline int ChatEntryWidget::text_margin     = 15;
inline int ChatEntryWidget::text_rounding   = 5;
inline int ChatEntryWidget::header_pix_size = 42;


/*
 *  对话展示框
 */
class ChatHistoryWidget : public QWidget {
    Q_OBJECT
public:
    explicit ChatHistoryWidget(QWidget *parent);

    void AddHistory(std::shared_ptr<ChatEntry> history);
    void AppendHistory(std::shared_ptr<ChatEntry> history);

private:
    QListWidget *chat_entrys_widget_;

    struct Entry {
        std::shared_ptr<ChatEntry> history;
        QListWidgetItem           *item;
    };
    QVector<Entry> entrys_;
};


#endif // OCHAT__WIDGET_CHAT_WIDGET__CHAT_HISTORY_WIDGET_H
