/*
 * Photos - access, organize and share your photos on GNOME
 * Copyright © 2013 – 2017 Red Hat, Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */


#include "config.h"

#include "photos-quarks.h"


GQuark
photos_quarks_flash_off_quark (void)
{
  return g_quark_from_static_string ("http://www.tracker-project.org/temp/nmm#flash-off");
}


GQuark
photos_quarks_flash_on_quark (void)
{
  return g_quark_from_static_string ("http://www.tracker-project.org/temp/nmm#flash-on");
}


GQuark
photos_quarks_orientation_bottom_quark (void)
{
  return g_quark_from_static_string ("http://www.semanticdesktop.org/ontologies/2007/03/22/nfo#orientation-bottom");
}


GQuark
photos_quarks_orientation_left_quark (void)
{
  return g_quark_from_static_string ("http://www.semanticdesktop.org/ontologies/2007/03/22/nfo#orientation-left");
}


GQuark
photos_quarks_orientation_right_quark (void)
{
  return g_quark_from_static_string ("http://www.semanticdesktop.org/ontologies/2007/03/22/nfo#orientation-right");
}


GQuark
photos_quarks_orientation_top_quark (void)
{
  return g_quark_from_static_string ("http://www.semanticdesktop.org/ontologies/2007/03/22/nfo#orientation-top");
}
