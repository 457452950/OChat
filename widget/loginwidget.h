#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

private:
    void onLoginBtnClicked();
    void onpwChkChanged(bool checked);

private:
    QLineEdit* user_name_;
    QLineEdit* password_;
    QCheckBox* password_mode_;
};
#endif // LOGINWIDGET_H
