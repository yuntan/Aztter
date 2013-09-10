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

#ifndef AZTTEROAUTH_H
#define AZTTEROAUTH_H

#include <QObject>
#include <QUrl>
#include <QSettings>

class KQOAuthManager;
class KQOAuthRequest;

class AztterOAuth : public QObject
{
    Q_OBJECT

	Q_PROPERTY(QString oauthUrl READ oauthUrl NOTIFY oauthUrlChanged)

public:
	// constractor
	AztterOAuth(QObject *parent = 0);

	// Q_PROPERTY READ function
	QString oauthUrl();
    
signals:
	// Q_PROPERTY NOTIFY function
	void oauthUrlChanged();

    void authorized();

private slots:
	// connected with signals in KQOAuth
	void onTemporaryTokenReceived(QString temporaryToken, QString temporaryTokenSecret);
	void onAuthorizationPageRequested(QUrl openWebPageUrl);
	void onAuthorizationReceived(QString token, QString verifier);
	void onAccessTokenReceived(QString token, QString tokenSecret);
	void onAuthorizedRequestDone();
	void onRequestReady(QByteArray);

private:
	KQOAuthManager *m_oauthManager;
	KQOAuthRequest *m_oauthRequest;
	QSettings *m_oauthSettings;
	QUrl m_oauthUrl;
};

#endif // AZTTEROAUTH_H
