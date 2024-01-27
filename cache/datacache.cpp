#include "datacache.h"

#include <QDebug>
#include <QtLogging>
#include <QMutexLocker>

DataCache* DataCache::instance_ = nullptr;

DataCache *DataCache::Init()
{
    instance_ = new DataCache;
    return instance_;
}

void DataCache::Clear()
{
    if (instance_) {
        delete instance_;
        instance_ = nullptr;
    }
}

DataCache *DataCache::GetInstance()
{
    return instance_;
}

DataCache::DataCache(QObject *parent)
    : QObject{parent}
{}

const QImage* DataCache::GetImage(QString url)
{
    QMutexLocker unique_lock(&this->image_mutex_);

    auto iter = this->image_cache_.find(url);
    if (iter != this->image_cache_.end()) {
        return &iter.value();
    }

    QImage img;
    auto ok = img.load(url);
    if (!ok) {
        qFatal() << "load " << url << " image err";
        return nullptr;
    } else {
        qDebug() << url << "read ok";
    }

    iter = this->image_cache_.insert(url, std::move(img));
    return &iter.value();
}
