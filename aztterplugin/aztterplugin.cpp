#include <QtQml/qqml.h>
#include "aztterplugin.h"
#include "aztterloadingpagehelper.h"
#include "aztteroauth.h"
#include "aztterstatusupdate.h"
#include "aztterhometlhelper.h"
#include "azttertweetenum.h"
#include "azttertweetlistmodel.h"

void AztterPlugin::registerTypes (const char *uri)
{
	//register the class AztterOAuth into QML as a "AztterOAuth" element version 1.0
	qmlRegisterType<AztterLoadingPageHelper>(uri, 1, 0, "AztterLoadingPageHelper");
	qmlRegisterType<AztterOAuth>(uri, 1, 0, "AztterOAuth");
	qmlRegisterType<AztterStatusUpdate>(uri, 1, 0, "AztterStatusUpdate");
	qmlRegisterType<AztterHomeTLHelper>(uri, 1, 0, "AztterHomeTLHelper");
	qmlRegisterType<AztterTweetEnum>(uri, 1, 0, "AztterTweetEnum");
	qmlRegisterType<AztterTweetListModel>(uri, 1, 0, "AztterTweetListModel");
}
