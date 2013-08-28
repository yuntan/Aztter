#include "aztterstatusupdate.h"

AztterStatusUpdate::AztterStatusUpdate(QObject *parent) : AztterAPIBase(parent)
{
}

QString AztterStatusUpdate::tweet()
{
	return m_tweet;
}

void AztterStatusUpdate::setTweet(QString &str)
{
//	if( oauthSettings.value("oauth_token").toString().isEmpty() ||
//        oauthSettings.value("oauth_token_secret").toString().isEmpty()) {
//        qDebug() << "No access tokens. Aborting.";

//        return;
//    }

//    oauthRequest->initRequest(KQOAuthRequest::AuthorizedRequest, QUrl("http://api.twitter.com/1/statuses/update.xml"));
//    oauthRequest->setConsumerKey("9PqhX2sX7DlmjNJ5j2Q");
//    oauthRequest->setConsumerSecretKey("1NYYhpIw1fXItywS9Bw6gGRmkRyF9zB54UXkTGcI8");
//    oauthRequest->setToken(oauthSettings.value("oauth_token").toString());
//    oauthRequest->setTokenSecret(oauthSettings.value("oauth_token_secret").toString());

//    KQOAuthParameters params;
//    params.insert("status", tweet);
//    oauthRequest->setAdditionalParameters(params);

//    oauthManager->executeRequest(oauthRequest);

//    connect(oauthManager, SIGNAL(requestReady(QByteArray)),
//            this, SLOT(onRequestReady(QByteArray)));
//    connect(oauthManager, SIGNAL(authorizedRequestDone()),
//            this, SLOT(onAuthorizedRequestDone()));
}
