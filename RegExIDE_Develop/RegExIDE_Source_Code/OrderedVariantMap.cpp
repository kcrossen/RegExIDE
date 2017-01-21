/****************************************************************************
**
** Copyright (C) 2016 Ken Crossen
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Redistributions in source code or binary form may not be sold.
**
****************************************************************************/

#include "OrderedVariantMap.h"

OrderedVariantMap::OrderedVariantMap ( ) : QMap<QString, QVariant> ( ) {

}

OrderedVariantMap::~OrderedVariantMap ( ) {

}

QStringList
OrderedVariantMap::orderedKeys ( ) const {
    return Ordered_Keys;
}

void
OrderedVariantMap::clear ( ) {
    Ordered_Keys.clear();
    QMap::clear();
}

void
OrderedVariantMap::insert ( const QString &key,
                            const QVariant &value ) {
    // Since QMap::insert will overwrite the value a previous instance of this key ...
    // ... w/ new value, treat this as new insertion.
    if (Ordered_Keys.contains(key)) Ordered_Keys.removeAt(Ordered_Keys.indexOf(key));
    Ordered_Keys.append(key);
    QMap::insert(key, value);
}

const QVariant
OrderedVariantMap::operator[] ( const QString &key ) const {
    return this->value(key);
}

QVariant&
OrderedVariantMap::operator[] ( const QString &key ) {
    // Since QMap::operator[] returns the address of an existing instance of this key ...
    // (if any), calling code may overwrite any previous instance of this key's value ...
    // ... w/ new value. Treating this as new insertion destroys the ordering ...
    // ... whenever value is read, e.g.
    //     QString category_name = regex_descr["Category"].toString();
    // The following code treats as new insertion (don't do this):
    // if (Ordered_Keys.contains(key)) Ordered_Keys.removeAt(Ordered_Keys.indexOf(key));
    // Ordered_Keys.append(key);

    // Net effect of this code, keys are ordered by first insertion of given key.
    if (not Ordered_Keys.contains(key)) Ordered_Keys.append(key);
    return QMap::operator [](key);
}

const QString
OrderedVariantMap::orderedKey ( int index ) const {
    return Ordered_Keys[index];
}

const QVariant
OrderedVariantMap::orderedValue ( int index ) const {
    return this->value(Ordered_Keys[index]);
}
