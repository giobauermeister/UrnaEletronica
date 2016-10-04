#include "urnaplugin_plugin.h"
#include "urna.h"

#include <qqml.h>

void UrnaPluginPlugin::registerTypes(const char *uri)
{
    // @uri Urna
    // aqui pode-se colocar a versão do plugin, no caso, 1.0
    qmlRegisterType<Urna>(uri, 1, 0, "Urna");
}

