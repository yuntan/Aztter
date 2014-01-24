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
        UserVerified,
        RT,
        RTUserId,
        RTUserName,
        RTUserScreenName,
        RTUserProfileImageUrl,
        RTUserVerified,
    };
};

#endif // AZTTERTWEETENUM_H
