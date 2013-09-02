#ifndef AZTTERHOMETLHELPER_H
#define AZTTERHOMETLHELPER_H

#include <QObject>
#include "aztteruserstream.h"

class AztterHomeTLHelper : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QString name READ name)
	Q_PROPERTY(QString screenName READ screenName)
	Q_PROPERTY(QString text READ text)

public:
	explicit AztterHomeTLHelper(QObject *parent = 0);
	Q_INVOKABLE void startFetching();
	Q_INVOKABLE void streamDisconnect();

	QString name();
	QString screenName();
	QString text();

signals:
	void tweetReceived();
	void friendsListReceived();
	void directMessageReceived();
	void tweetDeleted();

private slots:
	void parseStream(const QByteArray&);

private:
	void parseTweet(const QJsonObject&);
	void parseFriendsList(const QJsonObject&);
	void parseDirectMessage(const QJsonObject&);
	void parseDeleteTweet(const QJsonObject&);

	AztterUserStream *m_stream;

	// tweet data
	QString m_name;
	QString m_screenName;
	QString m_text;
	qint64 m_deletedId;
};

#endif // AZTTERHOMETLHELPER_H
