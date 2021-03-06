/*
 * Photos - access, organize and share your photos on GNOME
 * Copyright © 2012 – 2017 Red Hat, Inc.
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

/* Based on code from:
 *   + Documents
 */

#ifndef PHOTOS_SELECTION_CONTROLLER_H
#define PHOTOS_SELECTION_CONTROLLER_H

#include <glib-object.h>

G_BEGIN_DECLS

#define PHOTOS_TYPE_SELECTION_CONTROLLER (photos_selection_controller_get_type ())

#define PHOTOS_SELECTION_CONTROLLER(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), \
   PHOTOS_TYPE_SELECTION_CONTROLLER, PhotosSelectionController))

#define PHOTOS_IS_SELECTION_CONTROLLER(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), \
   PHOTOS_TYPE_SELECTION_CONTROLLER))

typedef struct _PhotosSelectionController      PhotosSelectionController;
typedef struct _PhotosSelectionControllerClass PhotosSelectionControllerClass;

GType                       photos_selection_controller_get_type           (void) G_GNUC_CONST;

PhotosSelectionController  *photos_selection_controller_dup_singleton      (void);

void                        photos_selection_controller_freeze_selection   (PhotosSelectionController *self,
                                                                            gboolean                   freeze);

GList                      *photos_selection_controller_get_selection      (PhotosSelectionController *self);

gboolean                    photos_selection_controller_get_selection_mode (PhotosSelectionController *self);

void                        photos_selection_controller_set_selection      (PhotosSelectionController *self,
                                                                            GList                     *selection);

void                        photos_selection_controller_set_selection_mode (PhotosSelectionController *self,
                                                                            gboolean mode);

G_END_DECLS

#endif /* PHOTOS_SELECTION_CONTROLLER_H */
