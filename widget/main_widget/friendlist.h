#ifndef FRIENDLIST_H
#define FRIENDLIST_H

#include <QLabel>
#include <QListWidget>
#include <QTreeWidget>
#include <QWidget>

#include "../../data_structure/datasructures.h"

/**
 * 列表头
 */
class FriendListHeader : public QWidget {
    Q_OBJECT
public:
    explicit FriendListHeader(QWidget* parent = nullptr);

    void SetGroupName(const QString& name);
    void Set();

private:
    QLabel *arrow_;
    // 分组名
    QLabel *group_name_;
};


/*
 *  好友列表窗口
 */
class FriendList : public QWidget {
    Q_OBJECT
public:
    explicit FriendList(QWidget *parent = nullptr);

    void AddUser(QString group,  std::shared_ptr<UIUser> user);

signals:

private:
    struct _Group {
        bool folded{false};
        QListWidgetItem* header{nullptr};
        struct user_item {
            std::shared_ptr<UIUser> user;
            QListWidgetItem* item;
        };
        QVector<user_item> users_items;

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
        void SetHidden(bool hide) { is_hidden_ = hide;
        }
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

#endif // FRIENDLIST_H
