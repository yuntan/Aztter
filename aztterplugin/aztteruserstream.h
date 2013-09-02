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
	void streamReceived(const QByteArray&);
	// Emited when user stream is reconnected after failure
	// Usefull when user stream connection fails to fetch missed tweets with REST API
	void reconnected();
	// Emited when user stream doesn't connect and backoff timer reaches maximum value (300 seconds)
	// Usefull when users stream fails to revert to REST API
	void failureConnect();

public slots:
	void startFetching();
	void streamDisconnect();

private slots:
	void replyReadyRead();
	// called when connection is finished.
	void replyFinished();
	void replyTimeout();
	void sslErrors(const QList<QSslError>& errors);

private:
	QByteArray m_cachedResponse;
	QNetworkReply *m_reply;
	QTimer *m_backofftimer;
	QTimer *m_timeoutTimer;
	bool m_streamTryingReconnect;
};

#endif // AZTTERUSERSTREAM_H
