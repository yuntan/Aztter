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

#include "aztterhometlhelper.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>
#include <QStringList>
#include <QDebug>
#include "azttertweetenum.h"
#include "aztteruserstream.h"
#include "aztterfav.h"
#include "aztterrt.h"
#include "aztterstatusupdate.h"

AztterHomeTLHelper::AztterHomeTLHelper(QObject *parent) : QObject(parent)
{
	m_stream = new AztterUserStream(this);
	m_fav = new AztterFav(this);
	m_rt = new AztterRT(this);
	m_statusUpdate = new AztterStatusUpdate(this);

	connect(m_stream, SIGNAL( streamReceived(QByteArray) ), this, SLOT( parseStream(QByteArray) ));
	connect(m_fav, SIGNAL( finished(qint64,bool) ), this, SIGNAL( favChanged(qint64,bool) ));
//	connect(m_fav, SIGNAL( finished(AztterAPIBase::Status) ),
//			this, SLOT( onFinished(AztterAPIBase::Status) ));
//	connect(m_statusUpdate, SIGNAL( finished(AztterAPIBase::Status) ),
//			this, SIGNAL( onFinished(AztterAPIBase::Status) ));
}

AztterHomeTLHelper::~AztterHomeTLHelper()
{
	qDebug() << "AztterHomeTLHelper destroyed";
}

void AztterHomeTLHelper::startFetching() {m_stream->startFetching();}
void AztterHomeTLHelper::streamDisconnect() {m_stream->streamDisconnect();}

void AztterHomeTLHelper::fav(const qint64 tweetId) {m_fav->fav(tweetId);}
void AztterHomeTLHelper::unfav(const qint64 tweetId) {m_fav->unfav(tweetId);}
void AztterHomeTLHelper::rt(const qint64 tweetId) {m_rt->rt(tweetId);}
void AztterHomeTLHelper::favrt(const qint64 tweetId) {fav(tweetId); rt(tweetId);}

void AztterHomeTLHelper::parseStream(const QByteArray &data)
{
	QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

	if(jsonDoc.isObject()) {
		QJsonObject jsonObj = jsonDoc.object();
		if (jsonObj.contains("friends")) {
			qDebug() << "friends list received";
			parseFriendsList(jsonObj);
		} else if (jsonObj.contains("text")) {
			qDebug() << "tweet received";
			parseTweet(jsonObj);
		} else if (jsonObj.contains("delete")) {
			qDebug() << "delete received";
			parseDeleteTweet(jsonObj);
		} else if (jsonObj.contains("direct_message")) {
			qDebug() << "direct message received";
			parseDirectMessage(jsonObj);
		}
	}
}

void AztterHomeTLHelper::parseTweet(const QJsonObject &tweetObj)
{
	qDebug() << "tweetObj:" << tweetObj;
	QJsonObject tmpObj;
	if(tweetObj.contains("retweeted_status")) {
		QJsonObject userObj = tweetObj["user"].toObject();
		m_tweet["RT"] = true;
		m_tweet["RTUserId"] = static_cast<qint64>(userObj["id"].toDouble());
		m_tweet["RTUserName"] = userObj["name"].toString();
		m_tweet["RTUserScreenName"] = userObj["screen_name"].toString();
		m_tweet["RTUserProfileImageUrl"] = userObj["profile_image_url"].toString();
		m_tweet["RTUserVerified"] = userObj["verified"].toBool();
		tmpObj = tweetObj["retweeted_status"].toObject();
	} else {
		m_tweet["RT"] = false;
		m_tweet["RTUserId"] = 0;
		m_tweet["RTUserName"] = "";
		m_tweet["RTUserScreenName"] = "";
		m_tweet["RTUserProfileImageUrl"] = "";
		m_tweet["RTUserVerified"] = false;
		tmpObj = tweetObj;
	}
	m_tweet["TweetId"] = static_cast<qint64>(tmpObj["id"].toDouble());
	m_tweet["TweetText"] = tmpObj["text"].toString();
	m_tweet["TweetCreatedAt"] = parseCreatedAt(tmpObj["created_at"].toString());
	m_tweet["TweetSource"] = tmpObj["source"].toString();
	m_tweet["TweetFavorited"] = tmpObj["favorited"].toBool();
	m_tweet["TweetRetweeted"] = tmpObj["retweeted"].toBool();

	QString id = tmpObj["in_reply_to_status_id"].toString();
	id == "null" ? m_tweet["TweetInReplyToStatusId"] = QVariant() // insert null
			: m_tweet["TweetInReplyToStatusId"] = static_cast<qint64>(id.toDouble());

	QJsonObject userObj = tmpObj["user"].toObject();
	m_tweet["UserId"] = static_cast<qint64>(userObj["id"].toDouble());
	m_tweet["UserName"] = userObj["name"].toString();
	m_tweet["UserScreenName"] = userObj["screen_name"].toString();
	m_tweet["UserProfileImageUrl"] = userObj["profile_image_url"].toString();
	m_tweet["UserVerified"] = userObj["verified"].toBool();

	emit tweetReceived(m_tweet);
}

void AztterHomeTLHelper::parseFriendsList(const QJsonObject &jsonObj)
{
	// TODO parse friendslist
	Q_UNUSED(jsonObj)
	emit friendsListReceived();
}

void AztterHomeTLHelper::parseDirectMessage(const QJsonObject &jsonObj)
{
	// TODO parse directmessaga
	Q_UNUSED(jsonObj)
	emit directMessageReceived();
}

void AztterHomeTLHelper::parseDeleteTweet(const QJsonObject &jsonObj)
{
	QJsonObject deleteStatusJson = jsonObj["delete"].toObject();
	QJsonObject statusJson = deleteStatusJson["status"].toObject();

	emit tweetDeleted( static_cast<qint64>(statusJson["id"].toDouble()) );
}

// QDateTime and QDate uses system local month name so they don't work well on
// non English environment
QDateTime AztterHomeTLHelper::parseCreatedAt(const QString &str)
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
