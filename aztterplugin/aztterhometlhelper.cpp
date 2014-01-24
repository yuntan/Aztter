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

#include "aztterhometlhelper.h"
#include "aztteruserstream.h"
#include "aztterhometl.h"
#include "aztterfav.h"
#include "aztterrt.h"
#include "aztterstatusupdate.h"

AztterHomeTLHelper::AztterHomeTLHelper(QObject *parent) : QObject(parent)
{
    m_stream = new AztterUserStream(this);
    m_homeTL = new AztterHomeTL(this);
    m_fav = new AztterFav(this);
    m_rt = new AztterRT(this);
    m_statusUpdate = new AztterStatusUpdate(this);

    connect(m_stream, SIGNAL( tweetReceived(QVariantMap) ), this, SIGNAL( tweetReceived(QVariantMap) ));
    connect(m_stream, SIGNAL( friendsListReceived() ), this, SIGNAL( friendsListReceived() ));
    connect(m_stream, SIGNAL( directMessageReceived() ), this, SIGNAL( directMessageReceived() ));
    connect(m_stream, SIGNAL( tweetDeleted(qint64) ), this, SIGNAL( tweetDeleted(qint64) ));
    connect(m_homeTL, SIGNAL( tweetReceived(QVariantMap) ), this, SIGNAL( tweetReceived(QVariantMap) ));
    connect(m_fav, SIGNAL( finished(qint64,bool) ), this, SIGNAL( favChanged(qint64,bool) ));
//	connect(m_fav, SIGNAL( finished(AztterAPIBase::Status) ),
//			this, SLOT( onFinished(AztterAPIBase::Status) ));
//	connect(m_statusUpdate, SIGNAL( finished(AztterAPIBase::Status) ),
//			this, SIGNAL( onFinished(AztterAPIBase::Status) ));
}

AztterHomeTLHelper::~AztterHomeTLHelper()
{
    qDebug() << "AztterHomeTLHelper destroyed";
}

void AztterHomeTLHelper::startFetching()
{
    m_homeTL->fetchTimeline();
    m_stream->startFetching();
}
void AztterHomeTLHelper::streamDisconnect() {m_stream->streamDisconnect();}

void AztterHomeTLHelper::fav(const qint64 tweetId) {m_fav->fav(tweetId);}
void AztterHomeTLHelper::unfav(const qint64 tweetId) {m_fav->unfav(tweetId);}
void AztterHomeTLHelper::rt(const qint64 tweetId) {m_rt->rt(tweetId);}
void AztterHomeTLHelper::favrt(const qint64 tweetId) {fav(tweetId); rt(tweetId);}
