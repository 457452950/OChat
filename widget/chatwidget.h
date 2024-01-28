#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>


#include "../data_structure/datasructures.h"

/* 输入框 */
class InputWidget : public QWidget {
public:
    explicit InputWidget(QWidget* parent = nullptr);

    class Listeaner {
    public:
        ~Listeaner() = default;

        virtual void UserInput(const QString& text) = 0;
    };

    void SetListeaner(Listeaner *new_listeaner);

private:
    QPushButton* image_;
    QPushButton* more_;
    QTextEdit* input_;

    Listeaner* listeaner_;
};


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
    InputWidget* input_;

    QWidget* wid_;

    /* data */
    std::shared_ptr<ChatGroup> group_;
};

#endif // CHATWIDGET_H
