#ifndef CHATGROUPLIST_H
#define CHATGROUPLIST_H

#include <QListWidget>
#include <QTreeWidget>
#include <QWidget>


#include "../../data_structure/datasructures.h"
#include "friendlist.h"

/*
 *  群聊列表窗口
 */
class ChatGroupList : public QWidget {
    Q_OBJECT
public:
    explicit ChatGroupList(QWidget *parent = nullptr);

    void AddChatGroup(QString group_str, std::shared_ptr<ChatGroup> chat_group);

signals:

private:
    struct _Group {
        bool folded{false};
        QListWidgetItem* header{nullptr};
        struct chat_group_item {
            std::shared_ptr<ChatGroup> chat_group;
            QListWidgetItem* item;
        };
        QVector<chat_group_item> chat_groups_items;

        _Group() {}
        ~_Group() {}
        _Group(const _Group&) = delete;
        _Group& operator=(const _Group&) = delete;
    };

    class PrivateListItem : public QListWidgetItem {
    public:
        PrivateListItem(QString group_name, bool is_header)
            : is_header(is_header), group_name_(group_name) {
        }
        ~PrivateListItem() {}

        QString GroupName() const {return group_name_;}
        bool IsHidden() const { return is_hidden_; }
        void SetHidden(bool hide) { is_hidden_ = hide; }
        const bool is_header;
    private:
        QString group_name_;
        bool is_hidden_{false};
    };

private slots:
    void slot_ListItemClicked(QListWidgetItem* item);
    void slot_ListItemDClicked(QListWidgetItem* item);

private:
    // layout
    QListWidget* root_;

    std::unordered_map<QString, std::shared_ptr<_Group>> groups_;
};


#endif // CHATGROUPLIST_H
