#include "clientconfig.h"

ClientConfig* ClientConfig::instance_ = nullptr;

ClientConfig *ClientConfig::Init()
{
    instance_ = new ClientConfig();
    return instance_;
}

void ClientConfig::Clear()
{
    if (instance_ != nullptr) {
        delete instance_;
        instance_ = nullptr;
    }
}

ClientConfig *ClientConfig::GetInstance()
{
    return instance_;
}

ClientConfig::ClientConfig() {}

QSize ClientConfig::GetMainWindowSize()
{
    return {300, 800};
}

QSize ClientConfig::GetLoginWindowSize()
{
    return {300, 200};
}
