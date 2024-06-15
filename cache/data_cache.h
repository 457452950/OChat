#ifndef OCHAT__CACHE__DATA_CACHE_H
#define OCHAT__CACHE__DATA_CACHE_H

#include <QObject>
#include <QImage>
#include <QMap>
#include <QMutex>

#include <lazybox/toy/Instance.hpp>

class DataCache : public QObject, public lbox::Instance<DataCache> {
    friend class lbox::Instance<DataCache>;
    Q_OBJECT

private:
    explicit DataCache(QObject *parent = nullptr);

public:
    const QImage *GetImage(QString url);

signals:

private:
    QImage *store(const QString &url);
    QImage *get(const QString &url);

    QMap<QString, QImage> image_cache_;
    QMutex                image_mutex_;
};

#endif // OCHAT__CACHE__DATA_CACHE_H
