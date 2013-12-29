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

#include <QApplication>
#include <QClipboard>
#include "aztterplugin.h"
#include "aztterauthhelper.h"
#include "aztterstatusupdate.h"
#include "azttertweetenum.h"
#include "azttertweetlistmodel.h"
#include "aztteruserstream.h"
#include "aztterhometl.h"
#include "aztterfav.h"
#include "aztterrt.h"

AztterPlugin::AztterPlugin(QObject *parent) : QObject(parent)
{
	m_clipboard = QApplication::clipboard();
	m_stream = new AztterUserStream(this);
	m_homeTL = new AztterHomeTL(this);
	m_fav = new AztterFav(this);
	m_rt = new AztterRT(this);
	m_statusUpdate = new AztterStatusUpdate(this);

	connect(m_clipboard, SIGNAL( dataChanged() ),
			this, SIGNAL( clipboardChanged() ));
	connect(m_stream, SIGNAL( tweetReceived(QVariantMap) ),
			this, SIGNAL( tweetReceived(QVariantMap) ));
	connect(m_stream, SIGNAL( friendsListReceived() ),
			this, SIGNAL( friendsListReceived() ));
	connect(m_stream, SIGNAL( directMessageReceived() ),
			this, SIGNAL( directMessageReceived() ));
	connect(m_stream, SIGNAL( tweetDeleted(qint64) ),
			this, SIGNAL( tweetDeleted(qint64) ));
	connect(m_homeTL, SIGNAL( tweetReceived(QVariantMap) ),
			this, SIGNAL( tweetReceived(QVariantMap) ));
	connect(m_fav, SIGNAL( finished(qint64,bool) ),
			this, SIGNAL( favChanged(qint64,bool) ));
//	connect(m_fav, SIGNAL( finished(AztterAPIBase::Status) ),
//			this, SLOT( onFinished(AztterAPIBase::Status) ));
	connect(m_statusUpdate, SIGNAL( postStatusChanged() ),
			this, SIGNAL( postStatusChanged() ));
}

void AztterPlugin::startAuth()
{
	m_authHelper = new AztterAuthHelper();
	connect(m_authHelper, SIGNAL(authPageRequested(QString)),
			this, SIGNAL(authPageRequested(QString)));
	connect(m_authHelper, SIGNAL(authorized()),
			this, SIGNAL(authorized()));
}

void AztterPlugin::startFetching()
{
	m_homeTL->fetchTimeline();
	m_stream->startFetching();
}
void AztterPlugin::streamDisconnect() {m_stream->streamDisconnect();}

void AztterPlugin::fav(const qint64 tweetId) {m_fav->fav(tweetId);}
void AztterPlugin::unfav(const qint64 tweetId) {m_fav->unfav(tweetId);}
void AztterPlugin::rt(const qint64 tweetId) {m_rt->rt(tweetId);}
void AztterPlugin::favrt(const qint64 tweetId) {fav(tweetId); rt(tweetId);}

void AztterPlugin::tweet(const QString &tweet) {m_statusUpdate->updateStatus(tweet);}
AztterStatusUpdate::PostStatus AztterPlugin::postStatus() {return m_statusUpdate->postStatus();}
QString AztterPlugin::clipboard() {return m_clipboard->text();}
void AztterPlugin::setClipboard(const QString &str) {m_clipboard->setText(str);}
