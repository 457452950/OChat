#ifndef OCHAT__WIDGET_MAIN_WIDGET__CHAT_GROUPLIST_H
#define OCHAT__WIDGET_MAIN_WIDGET__CHAT_GROUPLIST_H

#include <QListWidget>
#include <QTreeWidget>
#include <QWidget>


#include "widget/wrapper.h"
#include "friend_list.h"

/*
 *  群聊列表窗口
 */
class RoomList : public QWidget {
    Q_OBJECT
public:
    explicit RoomList(QWidget *parent = nullptr);

signals:

private:
    struct Element {
        Element(QListWidget *widget, const QString &uid) : widget_(widget) {
            item_         = std::make_unique<QListWidgetItem>();
            shown_widget_ = std::make_unique<ShownBoard>();

            //
            shown_widget_->SetRoom(uid);

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
    //                     room id               widget
    std::vector<std::pair<QString, std::shared_ptr<Element>>> groups_;
};


#endif // OCHAT__WIDGET_MAIN_WIDGET__CHAT_GROUPLIST_H
