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

#ifndef AZTTERAPIBASE_H
#define AZTTERAPIBASE_H

#include <QObject>
#include <QUrl>
#include <QByteArray>
#include <QVariantMap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "kqoauthmanager.h"
#include "kqoauthrequest.h"

class AztterAPIBase : public QObject
{
	Q_OBJECT

public:
	explicit AztterAPIBase(QObject *parent = 0);
	void init(KQOAuthRequest::RequestHttpMethod method, const QUrl &requestEndpoint);

protected slots:
	virtual void onRequestReady(QByteArray) {}
	virtual void onAuthorizedRequestDone() {}

protected:
	KQOAuthManager *m_oauthManager;
	KQOAuthRequest *m_oauthRequest;
};

#endif // AZTTERAPIBASE_H
