#ifndef EWSFOLDER_P_H
#define EWSFOLDER_P_H

#include "EwsFolder.h"

#include <QObject>

#include "wsdl_Services.h"

class EwsFolderPrivate
{
public:
    EwsFolderPrivate();
    EwsFolderPrivate(const T__FolderType &value);
    virtual ~EwsFolderPrivate();

    T__FolderType folder;
    EwsFolder::WellKnownFolderName wellKnownFolderName;
    EwsEffectiveRights effectiveRights;
    QList<EwsPermission> permissions;
    QHash<QString, QString> changes;
    EwsConnection *connection;
};

#endif // EWSFOLDER_P_H
