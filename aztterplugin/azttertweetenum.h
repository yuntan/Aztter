#ifndef AZTTERTWEETENUM_H
#define AZTTERTWEETENUM_H

#include <QObject>

class AztterTweetEnum : public QObject
{
	Q_OBJECT
	Q_ENUMS(Roles)

public:
	enum Roles { //values accessed through data
		TweetIdRole = Qt::UserRole, // 256
		TweetTextRole,
		UserIdRole,
		UserNameRole,
		UserScreenNameRole,
		UserProfileImageUrlRole
	};
};

#endif // AZTTERTWEETENUM_H
