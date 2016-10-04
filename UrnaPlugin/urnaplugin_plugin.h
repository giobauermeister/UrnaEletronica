#ifndef URNAPLUGIN_PLUGIN_H
#define URNAPLUGIN_PLUGIN_H

#include <QQmlExtensionPlugin>

class UrnaPluginPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};

#endif // URNAPLUGIN_PLUGIN_H
