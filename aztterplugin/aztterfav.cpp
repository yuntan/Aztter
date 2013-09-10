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

#include "aztterfav.h"
#include <QDebug>

#define TWITTER_FAV_CREATE_URL "https://api.twitter.com/1.1/favorites/create.json"
#define TWITTER_FAV_DESTROY_URL "https://api.twitter.com/1.1/favorites/destroy.json"

AztterFav::AztterFav(QObject *parent) : AztterAPIBase(parent)
{
	m_reply = 0;
}

void AztterFav::fav(qint64 tweetId)
{
	init(KQOAuthRequest::POST, QUrl(TWITTER_FAV_CREATE_URL));
	KQOAuthParameters params;
	params.insert("id", QString().setNum(tweetId));
	m_oauthRequest->setAdditionalParameters(params);
	m_oauthManager->executeRequest(m_oauthRequest);
}

void AztterFav::unfav(qint64 tweetId)
{
	init(KQOAuthRequest::POST, QUrl(TWITTER_FAV_DESTROY_URL));
	KQOAuthParameters params;
	params.insert("id", QString().setNum(tweetId));
	m_oauthRequest->setAdditionalParameters(params);
	m_oauthManager->executeRequest(m_oauthRequest);
}

void AztterFav::onRequestReady(QByteArray response)
{
	qDebug() << "Response from twitter:" << response;

	QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
	if(jsonDoc.isObject()){
		QJsonObject jsonObj = jsonDoc.object();
		if(jsonObj.contains("errors")){
			QJsonObject errorObj = jsonObj["errors"].toArray().at(0).toObject();
			qDebug() << "error received";
			qDebug() << "code:" << errorObj["code"].toDouble() <<
						"message:" << errorObj["message"].toString();
//			emit finished(Status);
		} else if(jsonObj.contains("text")){
			qDebug() << "success";
			qint64 tweetId = static_cast<qint64>(jsonObj["id"].toDouble());
			bool fav = jsonObj["favorited"].toBool();
			emit finished(tweetId, fav);
		}
	}
}
