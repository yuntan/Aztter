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

#ifndef AZTTERPLUGIN_H
#define AZTTERPLUGIN_H

#include <QObject>
#include <QVariantMap>
#include <QAbstractListModel>
#include "aztterstatusupdate.h"

class QClipboard;
class AztterAuthHelper;
class AztterUserStream;
class AztterHomeTL;
class AztterFav;
class AztterRT;

class AztterPlugin : public QObject
{
	Q_OBJECT
	Q_ENUMS(AztterStatusUpdate::PostStatus)
	Q_PROPERTY(AztterStatusUpdate::PostStatus postStatus
			   READ postStatus NOTIFY postStatusChanged)
	Q_PROPERTY(QString clipboard READ clipboard WRITE setClipboard NOTIFY clipboardChanged)

public:
	explicit AztterPlugin(QObject *parent = 0);

	// AztterAuthHelper
	Q_INVOKABLE void startAuth();
	// AztterUserStream
	Q_INVOKABLE void startFetching();
	Q_INVOKABLE void streamDisconnect();
	// AztterFavRT
	Q_INVOKABLE void fav(qint64 tweetId);
	Q_INVOKABLE void unfav(qint64 tweetId);
	Q_INVOKABLE void rt(qint64 tweetId);
	Q_INVOKABLE void favrt(qint64 tweetId);
	// AztterStatusUpdate
	Q_INVOKABLE void tweet(const QString& tweet);

	// for Q_PROPERTY
	AztterStatusUpdate::PostStatus postStatus();
	QString clipboard();
	void setClipboard(const QString &str);

signals:
	void authPageRequested(QString authPageUrl);
	void authorized();
	void tweetReceived(QVariantMap tweet);
	void friendsListReceived();
	void directMessageReceived();
	void tweetDeleted(qint64 tweetId);
	void favChanged(qint64 tweetId, bool favorited);
	void postStatusChanged();
	void clipboardChanged();

private:
	QClipboard *m_clipboard;
	AztterAuthHelper *m_authHelper;
	AztterUserStream *m_stream;
	AztterHomeTL *m_homeTL;
	AztterFav *m_fav;
	AztterRT *m_rt;
	AztterStatusUpdate *m_statusUpdate;
};

#endif // AZTTERPLUGIN_H
