#include "azttertweetlistmodel.h"
#include <QDebug>
#include "azttertweetenum.h"

AztterTweetListModel::AztterTweetListModel(QObject *parent) : QAbstractListModel(parent)
{
	m_roles[AztterTweetEnum::TweetIdRole] = "tweetId";
	m_roles[AztterTweetEnum::TweetTextRole] = "tweetText";
	m_roles[AztterTweetEnum::UserIdRole] = "userId";
	m_roles[AztterTweetEnum::UserNameRole] = "userName";
	m_roles[AztterTweetEnum::UserScreenNameRole] = "userScreenName";
	m_roles[AztterTweetEnum::UserProfileImageUrlRole] = "userProfileImageUrl";
}

QVariant AztterTweetListModel::data(const QModelIndex &index, int role) const
{
	qDebug() << "AztterTweetListModel::data" << index.row() << role;

	if (index.row() < 0 || index.row() >= m_tweetList.count())
		return QVariant();

	return m_tweetList[index.row()]->at(role);
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

void AztterTweetListModel::prepend(const QVariantList &tweet)
{
	beginInsertRows(QModelIndex(), 0, 0);
	m_tweetList.prepend(new QVariantList(tweet));
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

QVariantList* AztterTweetListModel::get(int index) const
{
	if(index < 0 || index >= m_tweetList.count())
		return 0;
	else
		return m_tweetList[index];
}
