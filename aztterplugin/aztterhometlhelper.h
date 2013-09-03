#ifndef AZTTERHOMETLHELPER_H
#define AZTTERHOMETLHELPER_H

#include <QObject>
#include "aztteruserstream.h"

class AztterHomeTLHelper : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QVariantList tweet READ tweet)
	Q_PROPERTY(qint64 deletedId READ deletedId)

public:
	explicit AztterHomeTLHelper(QObject *parent = 0);
	Q_INVOKABLE void startFetching();
	Q_INVOKABLE void streamDisconnect();

	QVariantList tweet() const;
	qint64 deletedId() const;

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
	QVariantList m_tweet;
	qint64 m_deletedId;
};

#endif // AZTTERHOMETLHELPER_H
