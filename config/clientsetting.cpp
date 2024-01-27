#include "clientsetting.h"

ClientSetting* ClientSetting::instance_ = nullptr;

ClientSetting *ClientSetting::Init()
{
    instance_ = new ClientSetting();
    return instance_;
}

void ClientSetting::Clear()
{
    if (instance_ != nullptr) {
        delete instance_;
        instance_ = nullptr;
    }
}

ClientSetting *ClientSetting::GetInstance()
{
    return instance_;
}

ClientSetting::ClientSetting() {}

QSize ClientSetting::GetMainWindowSize()
{
    return {300, 800};
}

QSize ClientSetting::GetLoginWindowSize()
{
    return {300, 200};
}

QSize ClientSetting::GetChatWindowDefaultSize()
{
    return {800, 600};
}
