#ifndef AZTTERTWEETLISTMODEL_H
#define AZTTERTWEETLISTMODEL_H

#include <QAbstractListModel>

class AztterTweetListModel : public QAbstractListModel
{
	Q_OBJECT

	Q_PROPERTY(int count  READ count  NOTIFY countChanged)

public:
	explicit AztterTweetListModel(QObject *parent = 0);

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	QHash<int, QByteArray> roleNames() const;
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int count() const;

signals:
	void countChanged();

public slots:
	void prepend(const QVariantMap &tweet);
	void remove(int index);
	QVariantMap *get(int index) const;

private:
	QList<QVariantMap*> m_tweetList;
	QHash<int, QByteArray> m_roles;
};

#endif // AZTTERTWEETLISTMODEL_H
