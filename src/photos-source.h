/*
 * Photos - access, organize and share your photos on GNOME
 * Copyright © 2012 Red Hat, Inc.
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

#ifndef PHOTOS_SOURCE_H
#define PHOTOS_SOURCE_H

#include <glib-object.h>
#include <goa/goa.h>

G_BEGIN_DECLS

#define PHOTOS_TYPE_SOURCE (photos_source_get_type ())
#define PHOTOS_SOURCE(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), \
   PHOTOS_TYPE_SOURCE, PhotosSource))

#define PHOTOS_SOURCE_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), \
   PHOTOS_TYPE_SOURCE, PhotosSourceClass))

#define PHOTOS_IS_SOURCE(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), \
   PHOTOS_TYPE_SOURCE))

#define PHOTOS_IS_SOURCE_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), \
   PHOTOS_TYPE_SOURCE))

#define PHOTOS_SOURCE_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), \
   PHOTOS_TYPE_SOURCE, PhotosSourceClass))

#define PHOTOS_SOURCE_STOCK_ALL   "all"
#define PHOTOS_SOURCE_STOCK_LOCAL "local"

typedef struct _PhotosSource        PhotosSource;
typedef struct _PhotosSourceClass   PhotosSourceClass;
typedef struct _PhotosSourcePrivate PhotosSourcePrivate;

struct _PhotosSource
{
  GObject parent_instance;
  PhotosSourcePrivate *priv;
};

struct _PhotosSourceClass
{
  GObjectClass parent_class;
};

GType               photos_source_get_type               (void) G_GNUC_CONST;

PhotosSource       *photos_source_new                    (const gchar *id, const gchar *name, gboolean builtin);

PhotosSource       *photos_source_new_from_goa_object    (GoaObject *object);

gchar              *photos_source_get_filter             (PhotosSource *self);

G_END_DECLS

#endif /* PHOTOS_SOURCE_H */
