#ifndef AZTTERFAV_H
#define AZTTERFAV_H

#include "aztterapibase.h"

class AztterFav : public AztterAPIBase
{
	Q_OBJECT

public:
	explicit AztterFav(QObject *parent = 0);
	void fav(qint64 tweetId);
	void unfav(qint64 tweetId);

signals:
	void finished(bool success, qint64 tweetId, bool favorited);

private:
	void onRequestReady(QByteArray);
	QNetworkReply *m_reply;
};

#endif // AZTTERFAV_H
