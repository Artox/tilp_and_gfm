/*  tilp - a linking program for TI graphing calculators
 *  Copyright (C) 1999-2002  Romain Lievin
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef __TILP_VERSION__
#define __TILP_VERSION__

/*
  This file contains version number
  and library requirements.
*/

#ifdef __WIN32__
# define TILP_VERSION "5.11" // For Win32
#else
# define TILP_VERSION VERSION
#endif
#define LIB_CABLE_VERSION_REQUIRED  "3.1.6"
#define LIB_CALC_VERSION_REQUIRED   "3.3.2"
#define LIB_TIFFEP_VERSION_REQUIRED "1.2.0"

#endif

