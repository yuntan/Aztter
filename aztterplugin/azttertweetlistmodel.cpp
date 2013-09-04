#include "azttertweetlistmodel.h"
#include <QDebug>
#include "azttertweetenum.h"

AztterTweetListModel::AztterTweetListModel(QObject *parent) : QAbstractListModel(parent)
{
	m_roles[AztterTweetEnum::TweetId] = "tweetId";
	m_roles[AztterTweetEnum::TweetText] = "tweetText";
	m_roles[AztterTweetEnum::UserId] = "userId";
	m_roles[AztterTweetEnum::UserName] = "userName";
	m_roles[AztterTweetEnum::UserScreenName] = "userScreenName";
	m_roles[AztterTweetEnum::UserProfileImageUrl] = "userProfileImageUrl";
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
	case AztterTweetEnum::UserId :
		return tweet->value("UserId");
	case AztterTweetEnum::UserName :
		return tweet->value("UserName");
	case AztterTweetEnum::UserScreenName :
		return tweet->value("UserScreenName");
	case AztterTweetEnum::UserProfileImageUrl :
		return tweet->value("UserProfileImageUrl");
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

void AztterTweetListModel::remove(int index)
{
	beginRemoveRows(QModelIndex(), index, index);
	delete m_tweetList.takeAt(index);
	endRemoveRows();
	emit countChanged();
}

QVariantMap* AztterTweetListModel::get(int index) const
{
	if(index < 0 || index >= m_tweetList.count())
		return 0;
	else
		return m_tweetList[index];
}
