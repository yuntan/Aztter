#ifndef AZTTERUSERSTREAM_H
#define AZTTERUSERSTREAM_H

#include "aztterapibase.h"
#include <QObject>
#include <QList>

class QTimer;
class QSslError;

class AztterUserStream : public AztterAPIBase
{
	Q_OBJECT

public:
	explicit AztterUserStream(QObject *parent = 0);

signals:
	// emits tweets elements from stream
//	void statusesStream(const QTweetStatus& status);
	/**
	 *   Emits friends list of id of authenticated user.
	 *   Emited immediately after connecting to the user stream.
	 *   If there is no reconnect it won't be emited again.
	 */
//	void friendsList(const QList<qint64> friends);
	// emits direct message when is arrived in the stream
//	void directMessageStream(const QTweetDMStatus& directMessage);
	// emits deletion of status in the stream
//	void deleteStatusStream(qint64 id, qint64 userid);
	// Emited when user stream is reconnected after failure
	// Usefull when user stream connection fails to fetch missed tweets with REST API
	void reconnected();
	// Emited when user stream doesn't connect and backoff timer reaches maximum value (300 seconds)
	// Usefull when users stream fails to revert to REST API
	void failureConnect();

public slots:
	Q_INVOKABLE void startFetching();
	Q_INVOKABLE void streamDisconnect();

private slots:
	void replyReadyRead();
	// called when connection is finished.
	void replyFinished();
	void replyTimeout();
	void sslErrors(const QList<QSslError>& errors);

private:
	void parseStream(const QByteArray& );
	void parseFriendsList(const QJsonObject& streamObject);
	void parseDirectMessage(const QJsonObject &json);
	void parseDeleteStatus(const QJsonObject& json);

	QByteArray m_cachedResponse;
	QNetworkReply *m_reply;
	QTimer *m_backofftimer;
	QTimer *m_timeoutTimer;
	bool m_streamTryingReconnect;
};

#endif // AZTTERUSERSTREAM_H
