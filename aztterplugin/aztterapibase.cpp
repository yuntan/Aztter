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

#include "aztterapibase.h"
#include "aztterkeystore.h"

AztterAPIBase::AztterAPIBase(QObject *parent) : QObject(parent)
{
	m_oauthManager = new KQOAuthManager(this);
	m_oauthRequest = new KQOAuthRequest(this);
	m_settings = new QSettings(QSettings::NativeFormat, QSettings::UserScope, "Aztter", "Aztter", this);
	m_oauthRequest->setEnableDebugOutput(false);

	connect(m_oauthManager, SIGNAL(requestReady(QByteArray)),
			this, SLOT(onRequestReady(QByteArray)));
	connect(m_oauthManager, SIGNAL(authorizedRequestDone()),
			this, SLOT(onAuthorizedRequestDone()));
}

void AztterAPIBase::init(KQOAuthRequest::RequestHttpMethod method, const QUrl &requestEndpoint)
{
	m_oauthRequest->initRequest(KQOAuthRequest::AuthorizedRequest, requestEndpoint);
	m_oauthRequest->setHttpMethod(method);
	m_oauthRequest->setConsumerKey(AztterKeyStore::consumerKey());
	m_oauthRequest->setConsumerSecretKey(AztterKeyStore::consumerSecretKey());
	m_oauthRequest->setToken(m_settings->value("accounts/test/oauth_token").toString());
	m_oauthRequest->setTokenSecret(m_settings->value("accounts/test/oauth_token_secret").toString());
}
