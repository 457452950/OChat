#include "window_manager.h"

#include <QHBoxLayout>

#include "widget/login_widget.h"
#include "widget/main_widget.h"
#include "widget/chat_widget.h"


WindowManager::WindowManager() {
    this->login_wid_ = std::make_unique<LoginWidget>();
    this->login_wid_->show();
}

WindowManager::~WindowManager() {}

void WindowManager::CreateChatSession(const QString &uid) {
    this->chat_wids_.insert(uid, std::make_shared<ChatWidget>(uid));
}

void WindowManager::slot_LoginSuccess(const User &master) {
    this->main_wid_ = std::make_unique<MainWidget>(master);
    this->main_wid_->show();

    this->login_wid_->hide();
}

void WindowManager::slot_DestroyChatSession(const QString &uid) {
    auto it  = chat_wids_.find(uid);
    auto wid = it.value();

    if(wid->isHidden()) {
        chat_wids_.erase(it);
    }
}

void WindowManager::slot_DestroyAllChatSession() { chat_wids_.clear(); }
