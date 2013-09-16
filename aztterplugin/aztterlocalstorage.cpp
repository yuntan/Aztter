#include "aztterlocalstorage.h"
#include <QQmlEngine>
#include <QQmlComponent>

AztterLocalStorage::AztterLocalStorage(QObject *parent) : QObject(parent)
{
	engine = new QQmlEngine(this);
	component = new QQmlComponent(engine, "Storage.qml", this);
	storage = component->create();
}

bool AztterLocalStorage::isAuthenticated()
{
	QVariant r;
	QMetaObject::invokeMethod(storage, "isAuthenticated",
							  Q_RETURN_ARG(QVariant, r));
	return r.toBool();
}

QString AztterLocalStorage::screenName(int index)
{
	QVariant arg0 = QVariant(index), r;
	QMetaObject::invokeMethod(storage, "screenName",
							  Q_RETURN_ARG(QVariant, r),
							  Q_ARG(QVariant, arg0));
	return r.toString();
}

QString AztterLocalStorage::oauthToken(int index)
{
	QVariant arg0 = QVariant(index), r;
	QMetaObject::invokeMethod(storage, "oauthToken",
							  Q_RETURN_ARG(QVariant, r),
							  Q_ARG(QVariant, arg0));
	return r.toString();
}

QString AztterLocalStorage::oauthTokenSecret(int index)
{
	QVariant arg0 = QVariant(index), r;
	QMetaObject::invokeMethod(storage, "oauthTokenSecret",
							  Q_RETURN_ARG(QVariant, r),
							  Q_ARG(QVariant, arg0));
	return r.toString();
}

void AztterLocalStorage::addAccount(QString screenName, QString token, QString tokenSecret)
{
	QVariant v0 = QVariant(screenName), v1 = QVariant(token), v2 = QVariant(tokenSecret);
	QMetaObject::invokeMethod(storage, "addAccount",
							  Q_ARG(QVariant, v0), Q_ARG(QVariant, v1), Q_ARG(QVariant, v2));
}
