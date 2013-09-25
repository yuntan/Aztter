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
#include "aztterlocalstorage.h"

AztterAPIBase::AztterAPIBase(QObject *parent) : QObject(parent)
{
	m_oauthManager = new KQOAuthManager(this);
	m_oauthRequest = new KQOAuthRequest(this);
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

	AztterLocalStorage storage;
	m_oauthRequest->setToken(storage.oauthToken(0));
	m_oauthRequest->setTokenSecret(storage.oauthTokenSecret(0));
}

QVariantMap AztterAPIBase::parseTweet(const QJsonObject &tweetObj)
{
	qDebug() << "tweetObj:" << tweetObj;
	QJsonObject tmpObj;
	QVariantMap tweet;
	if(tweetObj.contains("retweeted_status")) {
		QJsonObject userObj = tweetObj["user"].toObject();
		tweet["RT"] = true;
		tweet["RTUserId"] = static_cast<qint64>(userObj["id"].toDouble());
		tweet["RTUserName"] = userObj["name"].toString();
		tweet["RTUserScreenName"] = userObj["screen_name"].toString();
		tweet["RTUserProfileImageUrl"] = userObj["profile_image_url"].toString();
		tweet["RTUserVerified"] = userObj["verified"].toBool();
		tmpObj = tweetObj["retweeted_status"].toObject();
	} else {
		tweet["RT"] = false;
		tmpObj = tweetObj;
	}
	tweet["TweetId"] = static_cast<qint64>(tmpObj["id"].toDouble());
	tweet["TweetText"] = tmpObj["text"].toString();
	tweet["TweetCreatedAt"] = parseCreatedAt(tmpObj["created_at"].toString());
	tweet["TweetSource"] = tmpObj["source"].toString();
	tweet["TweetFavorited"] = tmpObj["favorited"].toBool();
	tweet["TweetRetweeted"] = tmpObj["retweeted"].toBool();

	QString id = tmpObj["in_reply_to_status_id"].toString();
	id == "null" ? tweet["TweetInReplyToStatusId"] = QVariant() // insert null
			: tweet["TweetInReplyToStatusId"] = static_cast<qint64>(id.toDouble());

	QJsonObject userObj = tmpObj["user"].toObject();
	tweet["UserId"] = static_cast<qint64>(userObj["id"].toDouble());
	tweet["UserName"] = userObj["name"].toString();
	tweet["UserScreenName"] = userObj["screen_name"].toString();
	tweet["UserProfileImageUrl"] = userObj["profile_image_url"].toString();
	tweet["UserVerified"] = userObj["verified"].toBool();

	return tweet;
}

// QDateTime and QDate uses system local month name so they don't work well on
// non English environment
QDateTime AztterAPIBase::parseCreatedAt(const QString &str)
{
	/*
	 * twitter return string created_at like this
	 * "Tue Sep 10 04:41:30 +0000 2013"
	 *   0   1   2     3      4     5
	 */
	QStringList strList = str.split(" ");
	int month;
	QMap<QString, int> monthMap;
	monthMap["Jan"] = 1;
	monthMap["Feb"] = 2;
	monthMap["Mar"] = 3;
	monthMap["Apr"] = 4;
	monthMap["May"] = 5;
	monthMap["Jun"] = 6;
	monthMap["Jul"] = 7;
	monthMap["Aug"] = 8;
	monthMap["Sep"] = 9;
	monthMap["Oct"] = 10;
	monthMap["Nov"] = 11;
	monthMap["Dec"] = 12;
	month = monthMap[strList[1]];
	QDate date(strList[5].toInt(), month, strList[2].toInt());
	QTime time = QTime::fromString(strList[3], "hh:mm:ss");
	QDateTime dateTime(date, time, Qt::UTC); // twitter returns UTC time
	return dateTime.toLocalTime();
}
