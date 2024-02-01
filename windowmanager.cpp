#include "windowmanager.h"

#include <QHBoxLayout>

#include "widget/loginwidget.h"
#include "widget/mainwidget.h"
#include "widget/chatwidget.h"

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

void WindowManager::slot_LoginSuccess(std::shared_ptr<User> master)
{
    if (this->main_wid_ != nullptr) {
        delete this->main_wid_;
    }

    this->main_wid_ = new MainWidget(master);
    this->main_wid_->show();

    this->login_wid_->hide();
}

void WindowManager::slot_CreateChatSession(std::shared_ptr<ChatGroup> group)
{
    auto uid = group->Uid();
    auto it = chat_wids_.find(uid);
    if (it != chat_wids_.end()) {
        auto wid = it.value();
        if (wid->isHidden()) {
            wid->show();
        } else if (wid->isMinimized()){
            wid->showNormal();
        } else {
            wid->activateWindow();
        }

        qDebug() << group->Uid() << group->Name() << " window existed, show.";
        return;
    }
    qDebug() << group->Uid() << group->Name() << " window not existed, create.";

    auto chat_widget = new ChatWidget(group);
    this->chat_wids_.insert(uid, chat_widget);
    chat_widget->show();
}

void WindowManager::slot_DestroyChatSession(QString uid)
{
    auto it = chat_wids_.find(uid);
    auto wid = it.value();

    if (wid->isHidden()){
        delete wid;
        chat_wids_.erase(it);
    }
}

void WindowManager::slot_DestroyAllChatSession()
{
    for (auto it : this->chat_wids_){
        delete it;
    }
    chat_wids_.clear();
}
