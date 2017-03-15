/*
 * Photos - access, organize and share your photos on GNOME
 * Copyright © 2015 – 2017 Red Hat, Inc.
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

#ifndef PHOTOS_OPERATION_INSTA_CURVE_H
#define PHOTOS_OPERATION_INSTA_CURVE_H

#include <gegl-plugin.h>

G_BEGIN_DECLS

#define PHOTOS_TYPE_OPERATION_INSTA_CURVE (photos_operation_insta_curve_get_type ())
G_DECLARE_FINAL_TYPE (PhotosOperationInstaCurve,
                      photos_operation_insta_curve,
                      PHOTOS,
                      OPERATION_INSTA_CURVE,
                      GeglOperationPointFilter);

G_END_DECLS

#endif /* PHOTOS_OPERATION_INSTA_CURVE_H */
