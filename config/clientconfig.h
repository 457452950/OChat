#ifndef CLIENTCONFIG_H
#define CLIENTCONFIG_H

#include <QSize>

class ClientConfig
{
public:
    static ClientConfig* Init();
    static void Clear();
    static ClientConfig* GetInstance();

private:
    static ClientConfig* instance_;
    ClientConfig();

public:
    QSize GetMainWindowSize();
    QSize GetLoginWindowSize();

};

#endif // CLIENTCONFIG_H
