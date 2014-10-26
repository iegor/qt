/****************************************************************************
**
** Definition of signal/slot collections etc.
**
** Created : 980821
**
** Copyright (C) 1992-2008 Trolltech ASA.  All rights reserved.
**
** This file is part of the kernel module of the Qt GUI Toolkit.
**
** This file may be used under the terms of the GNU General
** Public License versions 2.0 or 3.0 as published by the Free
** Software Foundation and appearing in the files LICENSE.GPL2
** and LICENSE.GPL3 included in the packaging of this file.
** Alternatively you may (at your option) use any later version
** of the GNU General Public License if such license has been
** publicly approved by Trolltech ASA (or its successors, if any)
** and the KDE Free Qt Foundation.
**
** Please review the following information to ensure GNU General
** Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/.
** If you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** This file may be used under the terms of the Q Public License as
** defined by Trolltech ASA and appearing in the file LICENSE.QPL
** included in the packaging of this file.  Licensees holding valid Qt
** Commercial licenses may use this file in accordance with the Qt
** Commercial License Agreement provided with the Software.
**
** This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
** INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE. Trolltech reserves all rights not granted
** herein.
**
**********************************************************************/

#ifndef QSIGNALSLOTIMP_H
#define QSIGNALSLOTIMP_H

#ifndef QT_H
#include "qconnection.h"
#include "qptrlist.h"
#include "qptrvector.h"
#endif // QT_H

class Q_EXPORT QConnectionList : public QPtrList<QConnection>
{
public:
    QConnectionList() : QPtrList<QConnection>() {}
    QConnectionList( const QConnectionList &list ) : QPtrList<QConnection>(list) {}
   ~QConnectionList() { clear(); }
    QConnectionList &operator=(const QConnectionList &list)
	{ return (QConnectionList&)QPtrList<QConnection>::operator=(list); }
};

class Q_EXPORT QConnectionListIt : public QPtrListIterator<QConnection>
{
public:
    QConnectionListIt( const QConnectionList &l ) : QPtrListIterator<QConnection>(l) {}
    QConnectionListIt &operator=(const QConnectionListIt &i)
	{ return (QConnectionListIt&)QPtrListIterator<QConnection>::operator=(i); }
};

#if defined(Q_TEMPLATEDLL) && defined(Q_CC_INTEL)
// MOC_SKIP_BEGIN
Q_TEMPLATE_EXTERN template class Q_EXPORT QPtrVector<QConnectionList>;
#define Q_EXPORTED_QPTRVECTORCONNECTTIONLIST_TEMPLATES
// MOC_SKIP_END
#endif

class Q_EXPORT QSignalVec : public QPtrVector<QConnectionList>
{
public:
  QSignalVec(int sz=17) : QPtrVector<QConnectionList>(sz) {}
  QSignalVec( const QSignalVec &dict ) : QPtrVector<QConnectionList>(dict) {}
   ~QSignalVec() { clear(); }
  QSignalVec &operator=(const QSignalVec &dict) { return (QSignalVec&)QPtrVector<QConnectionList>::operator=(dict); }
  QConnectionList* at( uint index ) const  { return index >= size()? 0 : QPtrVector<QConnectionList>::at(index); }
  bool insert( uint index, const QConnectionList* d ) {
    if (index >= size() ) resize( 2*index + 1);
    return QPtrVector<QConnectionList>::insert(index, d);
  }
};

#define Q_DEFINED_QCONNECTION_LIST
#include "qwinexport.h"
#endif // QSIGNALSLOTIMP_H
