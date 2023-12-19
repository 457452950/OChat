#include "windowmanager.h"

#include <QHBoxLayout>

#include "widget/loginwidget.h"
#include "widget/mainwidget.h"

WindowManager* WindowManager::instance_ = nullptr;

WindowManager *WindowManager::Init()
{
    instance_ = new WindowManager;
    return instance_;
}

void WindowManager::Close()
{
    if (instance_ != nullptr) {
        delete instance_;
        instance_ = nullptr;
    }
}

WindowManager *WindowManager::GetInstance()
{
    return instance_;
}

WindowManager::WindowManager()
{
    this->login_wid_ = new LoginWidget();
    this->login_wid_->show();
}

void WindowManager::onLoginSuccess()
{
    if (this->main_wid_ != nullptr) {
        delete this->main_wid_;
    }

    this->main_wid_ = new MainWidget();
    this->main_wid_->show();

    this->login_wid_->hide();
}
