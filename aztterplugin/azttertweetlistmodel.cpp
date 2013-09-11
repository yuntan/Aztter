/*
 * Copyright 2013 Yuuto Tokunaga
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "azttertweetlistmodel.h"
#include <QDebug>
#include "azttertweetenum.h"

AztterTweetListModel::AztterTweetListModel(QObject *parent) : QAbstractListModel(parent)
{
	m_roles[AztterTweetEnum::TweetId] = "tweetId";
	m_roles[AztterTweetEnum::TweetText] = "tweetText";
	m_roles[AztterTweetEnum::TweetInReplyToStatusId] = "tweetInReplyToStatusId";
	m_roles[AztterTweetEnum::TweetCreatedAt] = "tweetCreatedAt";
	m_roles[AztterTweetEnum::TweetSource] = "tweetSource";
	m_roles[AztterTweetEnum::TweetFavorited] = "tweetFavorited";
	m_roles[AztterTweetEnum::TweetRetweeted] = "tweetRetweeted";
	m_roles[AztterTweetEnum::UserId] = "userId";
	m_roles[AztterTweetEnum::UserName] = "userName";
	m_roles[AztterTweetEnum::UserScreenName] = "userScreenName";
	m_roles[AztterTweetEnum::UserProfileImageUrl] = "userProfileImageUrl";
	m_roles[AztterTweetEnum::UserVerified] = "userVerified";
	m_roles[AztterTweetEnum::RT] = "rt";
	m_roles[AztterTweetEnum::RTUserId] = "rtUserId";
	m_roles[AztterTweetEnum::RTUserName] = "rtUserName";
	m_roles[AztterTweetEnum::RTUserScreenName] = "rtUserScreenName";
	m_roles[AztterTweetEnum::RTUserProfileImageUrl] = "rtUserProfileImageUrl";
	m_roles[AztterTweetEnum::RTUserVerified] = "rtUserVerified";
}

QVariant AztterTweetListModel::data(const QModelIndex &index, int role) const
{
//	qDebug() << "AztterTweetListModel::data" << index.row() << role;

	if (index.row() < 0 || index.row() >= m_tweetList.count())
		return QVariant();

	QVariantMap *tweet = m_tweetList[index.row()];
	switch (role) {
	case AztterTweetEnum::TweetId :
		return tweet->value("TweetId");
	case AztterTweetEnum::TweetText :
		return tweet->value("TweetText");
	case AztterTweetEnum::TweetInReplyToStatusId :
		return tweet->value("TweetInReplyToStatusId");
	case AztterTweetEnum::TweetCreatedAt :
		return tweet->value("TweetCreatedAt");
	case AztterTweetEnum::TweetSource :
		return tweet->value("TweetSource");
	case AztterTweetEnum::TweetFavorited :
		return tweet->value("TweetFavorited");
	case AztterTweetEnum::TweetRetweeted :
		return tweet->value("TweetRetweeted");
	case AztterTweetEnum::UserId :
		return tweet->value("UserId");
	case AztterTweetEnum::UserName :
		return tweet->value("UserName");
	case AztterTweetEnum::UserScreenName :
		return tweet->value("UserScreenName");
	case AztterTweetEnum::UserProfileImageUrl :
		return tweet->value("UserProfileImageUrl");
	case AztterTweetEnum::UserVerified :
		return tweet->value("UserVerified");
	case AztterTweetEnum::RT :
		return tweet->value("RT");
	case AztterTweetEnum::RTUserId :
		return tweet->value("RTUserId");
	case AztterTweetEnum::RTUserName :
		return tweet->value("RTUserName");
	case AztterTweetEnum::RTUserScreenName :
		return tweet->value("RTUserScreenName");
	case AztterTweetEnum::RTUserProfileImageUrl :
		return tweet->value("RTUserProfileImageUrl");
	case AztterTweetEnum::RTUserVerified :
		return tweet->value("RTUserVerified");
	default:
		return QVariant();
	}
}

QHash<int, QByteArray> AztterTweetListModel::roleNames() const
{
	return m_roles;
}

qint32 AztterTweetListModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return m_tweetList.count();
}

qint32 AztterTweetListModel::count() const
{
	return m_tweetList.count();
}

void AztterTweetListModel::prepend(const QVariantMap &tweet)
{
	beginInsertRows(QModelIndex(), 0, 0);
	m_tweetList.prepend(new QVariantMap(tweet));
	endInsertRows();
	emit countChanged();
}

void AztterTweetListModel::remove(const qint64 tweetId)
{
	for(int i = 0; i < m_tweetList.count(); i++) {
		if(m_tweetList[i]->value("TweetId") == tweetId) {
			beginRemoveRows(QModelIndex(), i, i);
			delete m_tweetList.takeAt(i);
			endRemoveRows();
			emit countChanged();
			return;
		}
	}
}

void AztterTweetListModel::changeFav(const qint64 tweetId, const bool fav)
{
	for(int i = 0; i < m_tweetList.count(); i++) {
		if(m_tweetList[i]->value("TweetId") == tweetId) {
			qDebug() << "changeFav";
			QVariantMap tweet = *(m_tweetList[i]);
			tweet.insert("TweetFavorited", fav);
			beginRemoveRows(QModelIndex(), i, i);
			delete m_tweetList.takeAt(i);
			endRemoveRows();
			beginInsertRows(QModelIndex(), i, i);
			m_tweetList.insert(i, new QVariantMap(tweet));
			endInsertRows();
			return;
		}
	}
}

QVariantMap* AztterTweetListModel::get(int index) const
{
	if(index < 0 || index >= m_tweetList.count())
		return 0;
	else
		return m_tweetList[index];
}
