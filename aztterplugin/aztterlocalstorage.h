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
	void addAccount(const QString& screenName, const QString& token, const QString& tokenSecret);

private:
	QQmlEngine *m_engine;
	QQmlComponent *m_component;
	QObject *m_storage;
};

#endif // AZTTERLOCALSTORAGE_H
