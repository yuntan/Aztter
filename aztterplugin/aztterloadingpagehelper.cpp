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
