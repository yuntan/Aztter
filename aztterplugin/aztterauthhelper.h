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

#ifndef AZTTERAUTHHELPER_H
#define AZTTEOAUTHHELPER_H

#include <QObject>
#include <QUrl>

class KQOAuthManager;
class KQOAuthRequest;

class AztterAuthHelper : public QObject
{
    Q_OBJECT

public:
    // constractor
    AztterAuthHelper(QObject *parent = 0);

signals:
    // Q_PROPERTY NOTIFY function
    void authPageRequested(QString authPageUrl);
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
    QString m_oauthToken;
    QString m_oauthTokenSecret;
};

#endif // AZTTERAUTHHELPER_H
