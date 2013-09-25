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
class AztterRT;
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
	Q_INVOKABLE void fav(qint64 tweetId);
	Q_INVOKABLE void unfav(qint64 tweetId);
	Q_INVOKABLE void rt(qint64 tweetId);
	Q_INVOKABLE void favrt(qint64 tweetId);

signals:
	void tweetReceived(QVariantMap tweet);
	void friendsListReceived();
	void directMessageReceived();
	void tweetDeleted(qint64 tweetId);
	void favChanged(qint64 tweetId, bool favorited);

private:
	AztterUserStream *m_stream;
	AztterFav *m_fav;
	AztterRT *m_rt;
	AztterStatusUpdate *m_statusUpdate;
};

#endif // AZTTERHOMETLHELPER_H
