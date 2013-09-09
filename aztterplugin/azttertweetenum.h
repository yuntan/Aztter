#ifndef AZTTERTWEETENUM_H
#define AZTTERTWEETENUM_H

#include <QObject>

class AztterTweetEnum : public QObject
{
	Q_OBJECT
	Q_ENUMS(Roles)

public:
	enum Roles { //values accessed through data
		TweetId = Qt::UserRole, // 256
		TweetText,
		TweetCreatedAt,
		TweetSource,
		TweetInReplyToStatusId,
		TweetFavorited,
		TweetRetweeted,
		UserId,
		UserName,
		UserScreenName,
		UserProfileImageUrl,
		UserVerified
	};
};

#endif // AZTTERTWEETENUM_H
