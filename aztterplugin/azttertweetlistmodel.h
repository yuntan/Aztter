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
    void remove(const qint64 tweetId);
    void changeFav(const qint64 tweetId, const bool fav);
    QVariantMap *get(int index) const;

private:
    QList<QVariantMap*> m_tweetList;
    QHash<int, QByteArray> m_roles;
};

#endif // AZTTERTWEETLISTMODEL_H
