#include "aztterhometl.h"

#define TWITTER_HOMETIMELINE_URL "https://api.twitter.com/1.1/statuses/home_timeline.json"

AztterHomeTL::AztterHomeTL(QObject *parent) : AztterAPIBase(parent)
{
}

void AztterHomeTL::fetchTimeline(qint64 sinceID, qint64 maxID)
{
    init(KQOAuthRequest::GET, QUrl(TWITTER_HOMETIMELINE_URL));

    KQOAuthParameters params;
    QString str;
    params.insert("count", str.setNum(50));
    if(sinceID)
        params.insert("since_id", str.setNum(sinceID));
    if(maxID)
        params.insert("max_id", str.setNum(maxID));

    m_oauthRequest->setAdditionalParameters(params);
    m_oauthManager->executeRequest(m_oauthRequest);
}

void AztterHomeTL::onRequestReady(QByteArray response)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
    if(jsonDoc.isObject()) { // error returned
        QJsonObject errorObj = jsonDoc.object().value("errors").toArray().at(0).toObject();
        qDebug() << "error received";
        qDebug() << "code:" << errorObj["code"].toDouble() <<
                    "message:" << errorObj["message"].toString();
        // TODO error handling
    } else if(jsonDoc.isArray()) { // tweet list returned
        QJsonArray jsonArray = jsonDoc.array();
        for(int i = jsonArray.size() - 1; i >= 0; i--) {
            emit tweetReceived(parseTweet(jsonArray[i].toObject()));
        }
    }
}

void AztterHomeTL::onAuthorizedRequestDone()
{
    qDebug() << "AztterHomeTL: Request sent to Twitter";
}
