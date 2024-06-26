#include "main_widget.h"

#include <QPixmap>
#include <QImage>
#include <QBoxLayout>
#include <QMenu>
#include <QMessageBox>

#include <lazybox/Assert.hpp>

#include "../window_manager.h"
#include "../common/config/client_setting.h"
#include "../cache/data_cache.h"


/*
 *  主页面
 */
MainWidget::MainWidget(const User &master, QWidget *parent) : QWidget{parent}, master_user_(master) {

    // setup ui
    this->resize(SETTING->MainWindowSize);
    this->setWindowFlag(Qt::WindowMaximizeButtonHint, false);
    this->setMinimumSize(SETTING->MainWindowMinimumSize);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    {
        master_board_ = new ShownBoard(this);
        master_board_->setMaximumHeight(100);
        mainLayout->addWidget(master_board_);
    }
    {
        auto tab_wid = new QTabWidget(this);
        tab_wid->tabBar()->setExpanding(true);
        {
            user_list_ = new SessionList(this);
            tab_wid->addTab(user_list_, "消息");
        }
        {
            auto sub_tab = new QTabWidget(this);
            {
                this->friend_list_ = new FriendList(this);
                sub_tab->addTab(this->friend_list_, "好友");
            }
            {
                this->room_list_ = new RoomList(this);
                sub_tab->addTab(this->room_list_, "群聊");
            }
            tab_wid->addTab(sub_tab, "联系人");
        }
        mainLayout->addWidget(tab_wid);
    }


    this->setLayout(mainLayout);

    this->master_board_->SetUser(master_user_.uid);

    ChangeManager.Register(this, {master_user_.uid});
}

MainWidget::~MainWidget() { ChangeManager.UnRegister(this); }

void MainWidget::closeEvent(QCloseEvent *event) {

    qDebug() << "main window close";
    WindowManager::GetInstance()->slot_DestroyAllChatSession();
    event->accept();

    // auto temp = QMessageBox::information(this, "确认", "是否关闭?", QMessageBox::Yes | QMessageBox::No);
    // if (temp == QMessageBox::Yes)
    // {
    //     qDebug() << "main window close";
    //     WindowManager::GetInstance()->slot_DestroyAllChatSession();
    //     event->accept();
    // }
    // else
    // {
    //     //忽略了 要关闭这个窗口的事件.当前窗口就不会被关闭.
    //     event->ignore();
    // }
}

void MainWidget::OnObjectUpdate(const ChangeEvent &event) {
    Assert(event.type == Mod);
    Assert(event.uid == this->master_user_.uid);
}
