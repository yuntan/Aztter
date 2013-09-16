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

#include <QtQml/qqml.h>
#include "aztterplugin.h"
#include "aztterauthhelper.h"
#include "aztterstatusupdate.h"
#include "aztterhometlhelper.h"
#include "azttertweetenum.h"
#include "azttertweetlistmodel.h"

void AztterPlugin::registerTypes (const char *uri)
{
	//register the class AztterOAuth into QML as a "AztterOAuth" element version 1.0
	qmlRegisterType<AztterAuthHelper>(uri, 1, 0, "AztterAuthHelper");
	qmlRegisterType<AztterStatusUpdate>(uri, 1, 0, "AztterStatusUpdate");
	qmlRegisterType<AztterHomeTLHelper>(uri, 1, 0, "AztterHomeTLHelper");
	qmlRegisterType<AztterTweetEnum>(uri, 1, 0, "AztterTweetEnum");
	qmlRegisterType<AztterTweetListModel>(uri, 1, 0, "AztterTweetListModel");
}
