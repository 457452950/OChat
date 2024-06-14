#include "data_cache.h"

#include <QDebug>
#include <QtLogging>
#include <QMutexLocker>


DataCache::DataCache(QObject *parent) : QObject{parent} {}

const QImage *DataCache::GetImage(QString url) {
    QMutexLocker unique_lock(&this->image_mutex_);

    auto iter = this->image_cache_.find(url);
    if(iter != this->image_cache_.end()) {
        return &iter.value();
    }

    QImage img;
    auto   ok = img.load(url);
    if(!ok) {
        qFatal() << "load " << url << " image err";
        return nullptr;
    } else {
        qDebug() << url << "read ok";
    }

    iter = this->image_cache_.insert(url, std::move(img));
    return &iter.value();
}
