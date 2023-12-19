#include "loginwidget.h"

#include <QBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

#include "../windowmanager.h"
#include "../config/clientconfig.h"

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

        QObject::connect(password_mode_, &QCheckBox::clicked, this, &LoginWidget::onpwChkChanged);

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

        QObject::connect(reqButton, &QPushButton::clicked, this, &LoginWidget::onLoginBtnClicked);
        QObject::connect(quitButton, &QPushButton::clicked, [this](){ this->close(); });

        buttonLayout->addWidget(reqButton);
        buttonLayout->addWidget(quitButton);

        mainLayout->addLayout(buttonLayout);
    }

    this->setLayout(mainLayout);
    this->setFixedSize(ClientConfig::GetInstance()->GetLoginWindowSize());
}

LoginWidget::~LoginWidget() {}

void LoginWidget::onLoginBtnClicked()
{
    qDebug("user:{%s},psd:{%s}", qUtf8Printable(this->user_name_->text()), qUtf8Printable(this->password_->text()));

    if (this->user_name_->text() == "asd" && this->password_->text() == "zxc") {
        WindowManager::GetInstance()->onLoginSuccess();
    }
}

void LoginWidget::onpwChkChanged(bool checked)
{
    this->password_->setEchoMode(!checked ? QLineEdit::EchoMode::Password : QLineEdit::EchoMode::Normal);
}

