/*
 * This file is part of the libews-qt project
 * Copyright (C) 2009 Dario Freddi <drf@kde.org>
 * Copyright (C) 2007 David Faure <faure@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB. If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef EWSEXPORT_H
#define EWSEXPORT_H

/** \file ewsexport.h
    \brief Contains Macros for exporting symbols

    This file contains macros needed for exporting/importing symbols
*/

#include <QtCore/QtGlobal>

#ifndef EWS_EXPORT
//# if defined(MAKE_EWS_LIB)
/* We are building this library */
#  define EWS_EXPORT Q_DECL_EXPORT
//# else
/* We are using this library */
//#  define EWS_EXPORT Q_DECL_IMPORT
//# endif
#endif

#endif // EWSEXPORT_H
