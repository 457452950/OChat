#ifndef OCHAT__WIDGET__LOGIN_WIDGET_H
#define OCHAT__WIDGET__LOGIN_WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>

class LoginWidget : public QWidget {
    Q_OBJECT

public:
    LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

private:
    void slot_LoginBtnClicked();
    void slot_PWChkChanged(bool checked);

private:
    QLineEdit *user_name_;
    QLineEdit *password_;
    QCheckBox *password_mode_;
};
#endif // OCHAT__WIDGET__LOGIN_WIDGET_H
