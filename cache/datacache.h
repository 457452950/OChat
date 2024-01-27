#ifndef DATACACHE_H
#define DATACACHE_H

#include <QObject>
#include <QImage>
#include <QMap>
#include <QMutex>

class DataCache : public QObject
{
    Q_OBJECT
public:
    static DataCache* Init();
    static void Clear();
    static DataCache* GetInstance();

public:
    const QImage* GetImage(QString url);

signals:

private:
    static DataCache* instance_;
    explicit DataCache(QObject *parent = nullptr);

    QMap<QString, QImage> image_cache_;
    QMutex image_mutex_;
};

#endif // DATACACHE_H
