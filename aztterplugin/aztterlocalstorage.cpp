#include "aztterlocalstorage.h"
#include <QVariant>
#include <QQmlEngine>
#include <QQmlComponent>

AztterLocalStorage::AztterLocalStorage(QObject *parent) : QObject(parent)
{
	m_engine = new QQmlEngine(this);
	m_component = new QQmlComponent(m_engine, QUrl("qrc:/qml/Storage.qml"), this);
	m_storage = m_component->create();
}

bool AztterLocalStorage::isAuthenticated()
{
	QVariant r;
	QMetaObject::invokeMethod(m_storage, "isAuthenticated",
							  Q_RETURN_ARG(QVariant, r));
	return r.toBool();
}

QString AztterLocalStorage::screenName(int index)
{
	QVariant arg0 = QVariant(index), r;
	QMetaObject::invokeMethod(m_storage, "screenName",
							  Q_RETURN_ARG(QVariant, r),
							  Q_ARG(QVariant, arg0));
	return r.toString();
}

QString AztterLocalStorage::oauthToken(int index)
{
	QVariant arg0 = QVariant(index), r;
	QMetaObject::invokeMethod(m_storage, "oauthToken",
							  Q_RETURN_ARG(QVariant, r),
							  Q_ARG(QVariant, arg0));
	return r.toString();
}

QString AztterLocalStorage::oauthTokenSecret(int index)
{
	QVariant arg0 = QVariant(index), r;
	QMetaObject::invokeMethod(m_storage, "oauthTokenSecret",
							  Q_RETURN_ARG(QVariant, r),
							  Q_ARG(QVariant, arg0));
	return r.toString();
}

void AztterLocalStorage::addAccount(const QString& screenName, const QString& token, const QString& tokenSecret)
{
	QVariant v0 = QVariant(screenName), v1 = QVariant(token), v2 = QVariant(tokenSecret);
	QMetaObject::invokeMethod(m_storage, "addAccount",
							  Q_ARG(QVariant, v0), Q_ARG(QVariant, v1), Q_ARG(QVariant, v2));
}
