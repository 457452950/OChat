#ifndef DATACACHE_H
#define DATACACHE_H

#include <QObject>

class DataCache : public QObject
{
    Q_OBJECT
public:
    explicit DataCache(QObject *parent = nullptr);

signals:
};

#endif // DATACACHE_H
