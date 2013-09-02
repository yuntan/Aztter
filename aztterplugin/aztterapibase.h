#ifndef AZTTERAPIBASE_H
#define AZTTERAPIBASE_H

#include <QObject>
#include <QUrl>
#include <QSettings>
#include <QByteArray>
#include "kqoauthmanager.h"
#include "kqoauthrequest.h"

class AztterAPIBase : public QObject
{
	Q_OBJECT

public:
	explicit AztterAPIBase(QObject *parent = 0);
	void init(KQOAuthRequest::RequestHttpMethod method, const QUrl &requestEndpoint);

protected slots:
	virtual void onRequestReady(QByteArray) {}
	virtual void onAuthorizedRequestDone() {}

protected:
	KQOAuthManager *m_oauthManager;
	KQOAuthRequest *m_oauthRequest;
	QSettings *m_settings;
};

#endif // AZTTERAPIBASE_H
