#ifndef AZTTERSTATUSUPDATE_H
#define AZTTERSTATUSUPDATE_H

#include "aztterapibase.h"
#include <QObject>
#include <QString>

class AztterStatusUpdate : public AztterAPIBase
{
	Q_OBJECT

	Q_PROPERTY(QString tweet READ tweet WRITE setTweet)

public:
	explicit AztterStatusUpdate(QObject *parent = 0);
	QString tweet();
	void setTweet(QString &str);

private slots:
	void onRequestReady(QByteArray);
	void onAuthorizedRequestDone();

private:
	QString m_tweet;
};

#endif // AZTTERSTATUSUPDATE_H
