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

#ifndef AZTTERUSERSTREAM_H
#define AZTTERUSERSTREAM_H

#include "aztterapibase.h"
#include <QObject>
#include <QList>

class QTimer;
class QSslError;

class AztterUserStream : public AztterAPIBase
{
	Q_OBJECT

public:
	explicit AztterUserStream(QObject *parent = 0);

signals:
	void streamReceived(const QByteArray&);
	// Emited when user stream is reconnected after failure
	// Usefull when user stream connection fails to fetch missed tweets with REST API
	void reconnected();
	// Emited when user stream doesn't connect and backoff timer reaches maximum value (300 seconds)
	// Usefull when users stream fails to revert to REST API
	void failureConnect();

public slots:
	void startFetching();
	void streamDisconnect();

private slots:
	void replyReadyRead();
	// called when connection is finished.
	void replyFinished();
	void replyTimeout();
	void sslErrors(const QList<QSslError>& errors);

private:
	QByteArray m_cachedResponse;
	QNetworkReply *m_reply;
	QTimer *m_backofftimer;
	QTimer *m_timeoutTimer;
	bool m_streamTryingReconnect;
};

#endif // AZTTERUSERSTREAM_H
