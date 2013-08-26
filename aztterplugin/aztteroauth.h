#ifndef AZTTEROAUTH_H
#define AZTTEROAUTH_H

#include <QObject>
#include "oauthtwitter.h"

class AztterOAuth : public QObject
{
    Q_OBJECT

	Q_PROPERTY(QUrl oauthUrl READ oauthUrl NOTIFY oauthUrlChanged)

	Q_PROPERTY(QString oauthPin READ oauthPin WRITE setOAuthPin)

public:
	// constractor
    AztterOAuth(QObject *parent = 0);

	// Q_PROPERTY READ function
	QUrl oauthUrl();
	QString oauthPin();

	// Q_PROPERTY WRITE function
	void setOAuthPin(QString &str);

	// accessible from QML
	Q_INVOKABLE void onPinEntered();
    
signals:
	// Q_PROPERTY NOTIFY function
	void oauthUrlChanged();

	void pleaseEnterPin();
    void authorized();

private slots:
	// connected with signals in OAuthTwitter
	void oauthPinAuthenticate();
	void accessGranted();
    void error();

private:
	OAuthTwitter *m_oauthTwitter;
	QUrl m_oauthUrl;
	QString m_oauthPin;
};

#endif // AZTTEROAUTH_H
