/*
 * Copyright 2013 Yuuto Tokunaga
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef AZTTERHOMETLHELPER_H
#define AZTTERHOMETLHELPER_H

#include <QObject>
#include <QVariantMap>

class AztterUserStream;
class AztterFav;
class AztterStatusUpdate;

class AztterHomeTLHelper : public QObject
{
	Q_OBJECT

public:
	explicit AztterHomeTLHelper(QObject *parent = 0);
	~AztterHomeTLHelper();

	// AztterUserStream
	Q_INVOKABLE void startFetching();
	Q_INVOKABLE void streamDisconnect();
	// AztterFavRT
	Q_INVOKABLE void fav(const qint64 tweetId);
	Q_INVOKABLE void unfav(const qint64 tweetId);
	Q_INVOKABLE void rt(const QString tweetText, const QString userScreenName);
	Q_INVOKABLE void favrt(const qint64 tweetId, const QString tweetText, const QString userScreenName);

signals:
	void tweetReceived(QVariantMap tweet);
	void friendsListReceived();
	void directMessageReceived();
	void tweetDeleted(qint64 tweetId);
	void favChanged(qint64 tweetId, bool favorited);

private slots:
	void parseStream(const QByteArray&);
	void onFinished(const qint64 tweetId, const bool fav);
//	void onFinished(AztterAPIBase::Status);

private:
	void parseTweet(const QJsonObject&);
	void parseFriendsList(const QJsonObject&);
	void parseDirectMessage(const QJsonObject&);
	void parseDeleteTweet(const QJsonObject&);

	AztterUserStream *m_stream;
	AztterFav *m_fav;
	AztterStatusUpdate *m_statusUpdate;
	QVariantMap m_tweet;
};

#endif // AZTTERHOMETLHELPER_H
