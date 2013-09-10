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

#include "aztterloadingpagehelper.h"
#include <QSettings>

AztterLoadingPageHelper::AztterLoadingPageHelper(QObject *parent) : QObject(parent)
{
	m_settings = new QSettings(QSettings::NativeFormat, QSettings::UserScope, "Aztter", "Aztter", this);
	if(m_settings->value("accounts/test/oauth_token") != QVariant()){
		m_loadingText = "Logging in...";
		m_isAuthenticated = true;
		emit loadingTextChanged();
	} else {
		m_isAuthenticated = false;
	}
}
