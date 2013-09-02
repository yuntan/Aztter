#include "aztterhometlhelper.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

AztterHomeTLHelper::AztterHomeTLHelper(QObject *parent) :
	QObject(parent)
{
	m_stream = new AztterUserStream(this);

	connect(m_stream, SIGNAL( streamReceived(QByteArray) ), this, SLOT( parseStream(QByteArray) ));
}

void AztterHomeTLHelper::startFetching()
{
	m_stream->startFetching();
}

void AztterHomeTLHelper::streamDisconnect()
{
	m_stream->streamDisconnect();
}

QString AztterHomeTLHelper::name()
{
	return m_name;
}

QString AztterHomeTLHelper::screenName()
{
	return m_screenName;
}

QString AztterHomeTLHelper::text()
{
	return m_text;
}

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

void AztterHomeTLHelper::parseTweet(const QJsonObject &jsonObj)
{
	m_text = jsonObj["text"].toString();

	QJsonObject userObj = jsonObj["user"].toObject();
	m_name = userObj["name"].toString();
	m_screenName = userObj["screen_name"].toString();

	emit tweetReceived();
}

void AztterHomeTLHelper::parseFriendsList(const QJsonObject &jsonObj)
{
	emit friendsListReceived();
}

void AztterHomeTLHelper::parseDirectMessage(const QJsonObject &jsonObj)
{
	emit directMessageReceived();
}

void AztterHomeTLHelper::parseDeleteTweet(const QJsonObject &jsonObj)
{
	QJsonObject deleteStatusJson = jsonObj["delete"].toObject();
	QJsonObject statusJson = deleteStatusJson["status"].toObject();

	m_deletedId = static_cast<qint64>(statusJson["id"].toDouble());

	emit tweetDeleted();
}
