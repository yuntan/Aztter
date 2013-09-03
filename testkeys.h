#ifndef AZTTERKEYSTORE_H
#define AZTTERKEYSTORE_H

#include <QObject>
#include <QString>

class AztterKeyStore : public QObject
{
	Q_OBJECT

public:
	explicit AztterKeyStore(QObject *parent = 0);
	static QString consumerKey() {return "uzf9lwFwNaHPqSafBXzyw";}
	static QString consumerSecretKey() {return "gYwf7nVp3UtlZNv7DOaRUV251QEARqfUpPbFs";}
};

#endif // AZTTERKEYSTORE_H

