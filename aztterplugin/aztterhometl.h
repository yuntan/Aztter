#ifndef AZTTERHOMETL_H
#define AZTTERHOMETL_H

#include "aztterapibase.h"

class AztterHomeTL : public AztterAPIBase
{
    Q_OBJECT

public:
    explicit AztterHomeTL(QObject *parent = 0);
    void fetchTimeline(qint64 sinceID = 0, qint64 maxID = 0);

signals:
    void tweetReceived(QVariantMap tweet);

private slots:
    void onRequestReady(QByteArray);
    void onAuthorizedRequestDone();
};

#endif // AZTTERHOMETL_H
