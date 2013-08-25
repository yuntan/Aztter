#include <QtQml/qqml.h>
#include "aztterplugin.h"
#include "aztteroauth.h"

void AztterPlugin::registerTypes (const char *uri)
{
    //register the class OAuth into QML as a "OAuth" element version 1.0
    qmlRegisterType<AztterOAuth>(uri, 1, 0, "AztterOAuth");
}
