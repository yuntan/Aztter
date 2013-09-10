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

#ifndef AZTTERLOADINGPAGEHELPER_H
#define AZTTERLOADINGPAGEHELPER_H

#include <QObject>

class QSettings;

class AztterLoadingPageHelper : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QString loadingText READ loadingText NOTIFY loadingTextChanged)
	Q_PROPERTY(bool isAuthenticated READ isAuthenticated)

public:
	explicit AztterLoadingPageHelper(QObject *parent = 0);

	QString loadingText() {return m_loadingText;}
	bool isAuthenticated() {return m_isAuthenticated;}
	
signals:
	void loadingTextChanged();

private:
	QSettings *m_settings;
	QString m_loadingText;
	bool m_isAuthenticated;
};

#endif // AZTTERLOADINGPAGEHELPER_H
