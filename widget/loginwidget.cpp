#include "loginwidget.h"

#include <QBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

#include "../windowmanager.h"
#include "../config/clientsetting.h"

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
{
    auto mainLayout = new QVBoxLayout(this);
    {
        mainLayout->addWidget(new QLabel("OChat", this), 0, Qt::AlignCenter);
    }
    {
        auto formLayout = new QGridLayout();

        user_name_ = new QLineEdit(this);
        password_ = new QLineEdit(this);
        password_mode_ = new QCheckBox(this);

        QObject::connect(password_mode_, &QCheckBox::clicked, this, &LoginWidget::slot_PWChkChanged);

        password_->setEchoMode(QLineEdit::Password);

        formLayout->addWidget(new QLabel("user name:", this), 0, 0);
        formLayout->addWidget(user_name_, 0, 1, 1, 2);

        formLayout->addWidget(new QLabel("password:", this), 1, 0);
        formLayout->addWidget(password_, 1, 1);
        formLayout->addWidget(password_mode_, 1, 2);

        mainLayout->addLayout(formLayout);
    }
    {
        auto buttonLayout = new QHBoxLayout();

        auto reqButton = new QPushButton("login", this);
        auto quitButton = new QPushButton("quit", this);

        QObject::connect(reqButton, &QPushButton::clicked, this, &LoginWidget::slot_LoginBtnClicked);
        QObject::connect(quitButton, &QPushButton::clicked, [this](){ this->close(); });

        buttonLayout->addWidget(reqButton);
        buttonLayout->addWidget(quitButton);

        mainLayout->addLayout(buttonLayout);
    }

    this->setLayout(mainLayout);
    this->setFixedSize(ClientSetting::GetInstance()->GetLoginWindowSize());
}

LoginWidget::~LoginWidget() {}

void LoginWidget::slot_LoginBtnClicked()
{
    qDebug("user:{%s},psd:{%s}", qUtf8Printable(this->user_name_->text()), qUtf8Printable(this->password_->text()));

#ifdef QT_DEBUG
    if (this->user_name_->text() == ClientSetting::DEBUG_GetDebugUser()->Name() && this->password_->text() == ClientSetting::DEBUG_login_password()) {
        WindowManager::GetInstance()->slot_LoginSuccess(ClientSetting::DEBUG_GetDebugUser());
        return;
    }
#endif
}

void LoginWidget::slot_PWChkChanged(bool checked)
{
    this->password_->setEchoMode(!checked ? QLineEdit::EchoMode::Password : QLineEdit::EchoMode::Normal);
}

