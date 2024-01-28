#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QObject>
#include <QMap>

#include "data_structure/datasructures.h"

class WindowManager : public QObject
{
    Q_OBJECT
public:
    static WindowManager* Init();
    static void Close();
    static WindowManager* GetInstance();

private:
    static WindowManager* instance_;
    WindowManager();

public slots:
    void slot_LoginSuccess(std::shared_ptr<User> master);
    void slot_CreateChatSession(std::shared_ptr<ChatGroup> group);
    void slot_DestroyChatSession(QString uid);
    void slot_DestroyAllChatSession();

signals:

private:
    QWidget* login_wid_{nullptr};
    QWidget* main_wid_{nullptr};

    // uid, widget
    QMap<QString, QWidget*> chat_wids_;
};

#endif // WINDOWMANAGER_H
