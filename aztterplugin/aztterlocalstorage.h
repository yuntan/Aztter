#ifndef AZTTERLOCALSTORAGE_H
#define AZTTERLOCALSTORAGE_H

#include <QObject>

class QQmlEngine;
class QQmlComponent;

class AztterLocalStorage : public QObject
{
	Q_OBJECT

public:
	explicit AztterLocalStorage(QObject *parent = 0);
	bool isAuthenticated();
	QString screenName(int index);
	QString oauthToken(int index);
	QString oauthTokenSecret(int index);
	void addAccount(QString screenName, QString token, QString tokenSecret);
	
private:
	QQmlEngine *engine;
	QQmlComponent *component;
	QObject *storage;
};

#endif // AZTTERLOCALSTORAGE_H
