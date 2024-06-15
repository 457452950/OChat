#include "data_cache.h"

#include <QDebug>
#include <QtLogging>
#include <QMutexLocker>

#include <lazybox/Assert.hpp>

#include "common/config/client_setting.h"


DataCache::DataCache(QObject *parent) : QObject{parent} { Assert(this->store(SETTING->UserNoneImage)); }

QImage *DataCache::store(const QString &url) {
    QMutexLocker unique_lock(&this->image_mutex_);
    QImage       img;
    bool         ok = img.load(url);
    if(ok) {
        qDebug() << url << "read ok";
        auto it = this->image_cache_.insert(url, std::move(img));
        return &it.value();
    }
    qWarning() << "load " << url << " image err";
    return nullptr;
}

QImage *DataCache::get(const QString &url) {
    QMutexLocker unique_lock(&this->image_mutex_);
    auto         iter = this->image_cache_.find(url);
    if(iter != this->image_cache_.end()) {
        return &iter.value();
    }
    return nullptr;
}


const QImage *DataCache::GetImage(QString url) {
    QImage *img = this->get(url);

    if(img) {
        return img;
    }

    img = this->store(url);

    if(img) {
        return img;
    }

    return nullptr;
}
