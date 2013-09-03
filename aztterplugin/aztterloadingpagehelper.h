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
