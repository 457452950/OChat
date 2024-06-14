#ifndef OCHAT____WINDOW_MANAGER_H
#define OCHAT____WINDOW_MANAGER_H

#include <memory>

#include <QObject>
#include <QMap>

#include <lazybox/toy/Instance.hpp>

#include "widget/wrapper.h"

class WindowManager : public QObject, public lbox::Instance<WindowManager> {
    Q_OBJECT

    friend class lbox::Instance<WindowManager>;

    WindowManager();
    ~WindowManager();

public:
    void CreateChatSession(const QString &uid);

public slots:
    void slot_LoginSuccess(const User &master);
    void slot_DestroyChatSession(const QString &uid);
    void slot_DestroyAllChatSession();

public:
    ObjectChangeList ChangeList;

private:
    std::unique_ptr<QWidget> login_wid_{nullptr};
    std::unique_ptr<QWidget> main_wid_{nullptr};

    // uid, widget
    QMap<QString, std::shared_ptr<QWidget>> chat_wids_;
};

#define ChangeManager WindowManager::GetInstance()->ChangeList

#endif // OCHAT____WINDOW_MANAGER_H
