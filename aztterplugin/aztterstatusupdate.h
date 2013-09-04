#ifndef AZTTERSTATUSUPDATE_H
#define AZTTERSTATUSUPDATE_H

#include "aztterapibase.h"
#include <QObject>

class QString;

class AztterStatusUpdate : public AztterAPIBase
{
	Q_OBJECT
	Q_ENUMS(Status)

	Q_PROPERTY(Status status READ status NOTIFY statusChanged)

public:
	explicit AztterStatusUpdate(QObject *parent = 0);

	enum Status {
		Success = Qt::UserRole,
		RateLimitExceeded, // code 88
		OverCapacity, // code 130
		InternalError, // code 131
		TimeInvalid, // code 135
		Duplicate, // code 187
		Unknown
	};

	Q_INVOKABLE void tweet(QString);
	Status status();

signals:
	void statusChanged();

private slots:
	void onRequestReady(QByteArray);
	void onAuthorizedRequestDone();

private:
	Status m_status;
};

#endif // AZTTERSTATUSUPDATE_H
