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

#ifndef ORDEREDVARIANTMAP_H
#define ORDEREDVARIANTMAP_H

#include <QtCore>
// OrderedVariantMap <= QVariant
#define toOrderedMap qvariant_cast<OrderedVariantMap>
// QVariant <= OrderedVariantMap
#define fromOrderedMap QVariant::fromValue

class OrderedVariantMap : public QMap<QString, QVariant> {

// Test:
//    OrderedVariantMap test_map;
//    test_map.insert("xxx", 1);
//    test_map.insert("aaa", 2);
//    test_map.insert("kkk", 3);

//    test_map["321"] = 4;
//    test_map["000"] = 5;
//    test_map["123"] = 6;

//    // Usual lexicographically ordered keys
//    qDebug() << "OrderedVariantMap.keys()" << test_map.keys();
//    // Keys returned by order of entry
//    qDebug() << "OrderedVariantMap.orderedKeys()" << test_map.orderedKeys();

//    QVariant test_variant = fromOrderedMap(test_map);
//    qDebug() << "test_variant.typeName()" << test_variant.typeName();
//    OrderedVariantMap test_map_recovered = toOrderedMap(test_variant);
//    qDebug() << "test_map_recovered.orderedKeys()" << test_map_recovered.orderedKeys();

// Test results:
//    OrderedVariantMap.keys() ("000", "123", "321", "aaa", "kkk", "xxx")
//    OrderedVariantMap.orderedKeys() ("xxx", "aaa", "kkk", "321", "000", "123")
//    test_variant.typeName() OrderedVariantMap
//    test_map_recovered.orderedKeys() ("xxx", "aaa", "kkk", "321", "000", "123")

public:
    OrderedVariantMap ( );
    ~OrderedVariantMap ( );

    void
    clear ( );

    void // QMap::iterator
    insert ( const QString &key,
             const QVariant &value );

    const QVariant
    operator[] ( const QString &key ) const;

    QVariant&
    operator[] ( const QString &key );

    const QString
    orderedKey ( int index ) const;

    const QVariant
    orderedValue ( int index ) const;

    QStringList
    orderedKeys ( ) const ;

private:
    QStringList Ordered_Keys;

protected:

};

Q_DECLARE_METATYPE(OrderedVariantMap)

#endif // ORDEREDVARIANTMAP_H
