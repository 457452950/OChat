#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QObject>
#include <QMap>

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

public:
    void onLoginSuccess();


signals:

private:
    QWidget* login_wid_{nullptr};
    QWidget* main_wid_{nullptr};
    QMap<QString, QWidget*> chat_wids_;
};

#endif // WINDOWMANAGER_H
