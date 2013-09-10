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
	void finished(qint64 tweetId, bool favorited);

private:
	void onRequestReady(QByteArray);
	QNetworkReply *m_reply;
};

#endif // AZTTERFAV_H
