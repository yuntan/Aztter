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

#ifndef AZTTERRT_H
#define AZTTERRT_H

#include "aztterapibase.h"

class AztterRT : public AztterAPIBase
{
	Q_OBJECT

public:
	explicit AztterRT(QObject *parent = 0);
	void rt(qint64 tweetId);
	
signals:
	void finished(qint64 rtId, bool success);
	
private:
	void onRequestReady(QByteArray);
	QNetworkReply *m_reply;
};

#endif // AZTTERRT_H
