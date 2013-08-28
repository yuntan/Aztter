#include <QtQml/qqml.h>
#include "aztterplugin.h"
#include "aztteroauth.h"
#include "aztterstatusupdate.h"

void AztterPlugin::registerTypes (const char *uri)
{
	//register the class AztterOAuth into QML as a "AztterOAuth" element version 1.0
	qmlRegisterType<AztterOAuth>(uri, 1, 0, "AztterOAuth");
	qmlRegisterType<AztterAPIBase>(uri, 1, 0, "AztterAPIBase");
	qmlRegisterType<AztterStatusUpdate>(uri, 1, 0, "AztterStatusUpdate");
}
