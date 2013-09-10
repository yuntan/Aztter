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

#include "aztterstatusupdate.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#define TWITTER_STATUSUPDATE_URL "http://api.twitter.com/1.1/statuses/update.json"

AztterStatusUpdate::AztterStatusUpdate(QObject *parent) : AztterAPIBase(parent)
{
}

void AztterStatusUpdate::tweet(QString tweet)
{
	init(KQOAuthRequest::POST, QUrl(TWITTER_STATUSUPDATE_URL));
//	init(KQOAuthRequest::GET, QUrl("https://api.twitter.com/1.1/statuses/home_timeline.json"));

	KQOAuthParameters params;
	params.insert("status", tweet);

	m_oauthRequest->setAdditionalParameters(params);
	m_oauthManager->executeRequest(m_oauthRequest);
}

AztterStatusUpdate::Status AztterStatusUpdate::status()
{
	return m_status;
}

void AztterStatusUpdate::onRequestReady(QByteArray response) {
//	qDebug() << "Response from the service: " << response;

	QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
	if(jsonDoc.isObject()) {
		QJsonObject jsonObj = jsonDoc.object();
		if(jsonObj.contains("errors")) {
			QJsonObject errorObj = jsonObj["errors"].toArray().at(0).toObject();
			qDebug() << "error received";
			qDebug() << "code:" << errorObj["code"].toDouble() <<
						"message:" << errorObj["message"].toString();
			switch ( static_cast<int>(errorObj["code"].toDouble()) ) {
			case 88:
				m_status = RateLimitExceeded;
				break;
			case 130:
				m_status = OverCapacity;
				break;
			case 131:
				m_status = InternalError;
				break;
			case 135:
				m_status = TimeInvalid;
				break;
			case 187:
				m_status = Duplicate;
				break;
			default:
				m_status = Unknown;
				break;
			}
			emit statusChanged();
		} else if(jsonObj.contains("text")){
			qDebug() << "tweet sent";
			m_status = Success;
			emit statusChanged();
		}
	}
}

void AztterStatusUpdate::onAuthorizedRequestDone() {
	qDebug() << "Request sent to Twitter";
}
