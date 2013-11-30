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

#ifndef AZTTERSTATUSUPDATE_H
#define AZTTERSTATUSUPDATE_H

#include "aztterapibase.h"
#include <QObject>

class QString;

class AztterStatusUpdate : public AztterAPIBase
{
	Q_OBJECT

public:
	explicit AztterStatusUpdate(QObject *parent = 0);

	enum PostStatus {
		Success = Qt::UserRole,
		RateLimitExceeded, // code 88
		OverCapacity, // code 130
		InternalError, // code 131
		TimeInvalid, // code 135
		Duplicate, // code 187
		Unknown
	};

	void updateStatus(const QString&);
	PostStatus postStatus();

signals:
	void postStatusChanged();

private slots:
	void onRequestReady(QByteArray);
	void onAuthorizedRequestDone();

private:
	PostStatus m_status;
};

#endif // AZTTERSTATUSUPDATE_H
