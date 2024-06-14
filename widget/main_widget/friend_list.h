#ifndef OCHAT__MAIN_WIDGET__FRIEND_LIST_H
#define OCHAT__MAIN_WIDGET__FRIEND_LIST_H

#include <memory>

#include <QLabel>
#include <QListWidget>
#include <QTreeWidget>
#include <QWidget>

#include <lazybox/Assert.hpp>

#include "window_manager.h"
#include "widget/wrapper.h"
#include "shown_board.h"


/*
 *  好友列表窗口
 */
class FriendList : public QWidget {
    Q_OBJECT
public:
    explicit FriendList(QWidget *parent = nullptr);

signals:

private:
    struct Element {
        Element(QListWidget *widget, const QString &uid) : widget_(widget) {
            item_         = std::make_unique<QListWidgetItem>();
            shown_widget_ = std::make_unique<ShownBoard>();

            //
            shown_widget_->SetUser(uid);

            // set ui
            widget_->addItem(item_.get());
            widget_->setItemWidget(item_.get(), shown_widget_.get());
        }
        ~Element() { widget_->removeItemWidget(item_.get()); }

    private:
        QListWidget                     *widget_{nullptr};
        std::unique_ptr<QListWidgetItem> item_;
        std::unique_ptr<ShownBoard>      shown_widget_;
    };

private slots:
    void slot_ListItemClicked(QListWidgetItem *item);
    void slot_ListItemDClicked(QListWidgetItem *item);

private:
    // layout
    QListWidget                                              *root_;
    //                     user id               widget
    std::vector<std::pair<QString, std::shared_ptr<Element>>> groups_;
};

#endif // OCHAT__MAIN_WIDGET__FRIEND_LIST_H
