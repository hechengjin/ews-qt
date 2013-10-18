#ifndef EWSUTILS_H
#define EWSUTILS_H

#include <QString>
#include <QMetaObject>
#include <QMetaEnum>

class EwsUtils
{
public:
    /**
     * Returns the string representing the enum
     * Useful for EwsTYPE::Enum
     */
    template<class T> static QString enumToString(const char *enumName, int value)
    {
        int id = T::staticMetaObject.indexOfEnumerator(enumName);
        QMetaEnum metaEnum = T::staticMetaObject.enumerator(id);

        return metaEnum.valueToKey(value);
    }

    template<class T> static int enumFromString(const char *enumName, const QString &key)
    {
        int id = T::staticMetaObject.indexOfEnumerator(enumName);
        QMetaEnum e = T::staticMetaObject.enumerator(id);

        return e.keyToValue(key.toLatin1().data());
    }
};

#endif // EWSUTILS_H
