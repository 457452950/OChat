#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QPushButton>
#include <QTextEdit>
#include <QWidget>


/* 输入框 */
class InputWidget : public QWidget {
    Q_OBJECT
public:
    explicit InputWidget(QWidget* parent = nullptr);

    class Listeaner {
    public:
        ~Listeaner() = default;

        virtual void UserInput(const QString& text) = 0;
    };

    void SetListeaner(Listeaner *new_listeaner);

private slots:
    void slot_BtnSendReleased();

private:
    QPushButton* image_;
    QPushButton* more_;

    QTextEdit* input_;

    QPushButton* send_;

    Listeaner* listeaner_;
};


#endif // INPUTWIDGET_H
