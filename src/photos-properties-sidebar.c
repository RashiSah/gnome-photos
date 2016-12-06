/*
 * Photos - access, organize and share your photos on GNOME
 * Copyright © 2016 Alessandro Bono
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

#include "photos-base-manager.h"
#include "photos-properties-sidebar.h"
#include "photos-fetch-collections-job.h"
#include "photos-filterable.h"
#include "photos-search-context.h"

struct _PhotosPropertiesSidebar
{
  GtkScrolledWindow parent_instance;
  GtkWidget *albums_list_box;
  GtkWidget *description_text_view;
  GtkWidget *source_grid;
  GtkWidget *title_entry;
  PhotosBaseItem *item;
};

struct _PhotosPropertiesSidebarClass
{
  GtkScrolledWindowClass parent_class;
};

G_DEFINE_TYPE (PhotosPropertiesSidebar, photos_properties_sidebar, GTK_TYPE_SCROLLED_WINDOW)

enum {
  PROP_0,
  N_PROPS
};

static GParamSpec *properties [N_PROPS];

GtkWidget *
photos_properties_sidebar_new (void)
{
  return g_object_new (PHOTOS_TYPE_PROPERTIES_SIDEBAR, NULL);
}

static void
photos_properties_sidebar_finalize (GObject *object)
{
  PhotosPropertiesSidebar *self = (PhotosPropertiesSidebar *)object;

  G_OBJECT_CLASS (photos_properties_sidebar_parent_class)->finalize (object);
}

static void
photos_properties_sidebar_get_property (GObject    *object,
                                        guint       prop_id,
                                        GValue     *value,
                                        GParamSpec *pspec)
{
  PhotosPropertiesSidebar *self = PHOTOS_PROPERTIES_SIDEBAR (object);

  switch (prop_id)
    {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
photos_properties_sidebar_on_collection_fetched (GObject *source_object,
                                                 GAsyncResult *res,
                                                 gpointer user_data)
{
  GApplication *app;
  GError *error = NULL;
  GList *collection_ids;
  GList *l;
  PhotosBaseManager *item_mngr;
  PhotosFetchCollectionsJob *job = PHOTOS_FETCH_COLLECTIONS_JOB (source_object);
  PhotosPropertiesSidebar *self = PHOTOS_PROPERTIES_SIDEBAR (user_data);
  PhotosSearchContextState *state;

  collection_ids = photos_fetch_collections_job_finish (job, res, &error);
  if (error != NULL)
    {
      g_warning ("Unable to fetch collections: %s", error->message);
      g_error_free (error);
    }

    app = g_application_get_default ();
    state = photos_search_context_get_state (PHOTOS_SEARCH_CONTEXT (app));
    item_mngr = g_object_ref (state->item_mngr);

    for (l = collection_ids; l != NULL; l = g_list_next (l))
      {
        const gchar *collection_name;
        const gchar *collection_id = l->data;
        PhotosBaseItem *collection;

        collection = PHOTOS_BASE_ITEM (photos_base_manager_get_object_by_id (item_mngr, collection_id));
        // avoid to show its folder as a collection
        if(!photos_base_item_is_collection (collection))
          continue;

        collection_name = photos_base_item_get_name (collection);
        GtkWidget *label = gtk_label_new (collection_name);
        gtk_widget_show (label);
        gtk_list_box_insert (GTK_LIST_BOX (self->albums_list_box), label, 0);
      }

  g_object_unref (self);
}

static void
photos_properties_sidebar_set_property (GObject      *object,
                                        guint         prop_id,
                                        const GValue *value,
                                        GParamSpec   *pspec)
{
  PhotosPropertiesSidebar *self = PHOTOS_PROPERTIES_SIDEBAR (object);

  switch (prop_id)
    {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
photos_properties_sidebar_class_init (PhotosPropertiesSidebarClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->finalize = photos_properties_sidebar_finalize;
  object_class->get_property = photos_properties_sidebar_get_property;
  object_class->set_property = photos_properties_sidebar_set_property;

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/Photos/properties-sidebar.ui");
  gtk_widget_class_bind_template_child (widget_class, PhotosPropertiesSidebar, albums_list_box);
  gtk_widget_class_bind_template_child (widget_class, PhotosPropertiesSidebar, description_text_view);
  gtk_widget_class_bind_template_child (widget_class, PhotosPropertiesSidebar, source_grid);
  gtk_widget_class_bind_template_child (widget_class, PhotosPropertiesSidebar, title_entry);
}

static void
photos_properties_sidebar_init (PhotosPropertiesSidebar *self)
{
  GtkWidget *label;

  gtk_widget_init_template (GTK_WIDGET (self));

  //TODO
  label = gtk_label_new("No albums");
  gtk_widget_show (label);
  gtk_list_box_set_placeholder (GTK_LIST_BOX (self->albums_list_box), label);

}

void
photos_properties_sidebar_set_item (PhotosPropertiesSidebar *self, PhotosBaseItem *item)
{
  GtkWidget *source_widget;
  const gchar *item_id;


  if (self->item != NULL)
    {
      GList *children;
      GList *l;

      g_object_unref (self->item);

      children = gtk_container_get_children (GTK_CONTAINER (self->albums_list_box));
      for(l = children; l != NULL; l = g_list_next(l))
        gtk_container_remove (GTK_CONTAINER (self->albums_list_box), GTK_WIDGET (l->data));

      children = gtk_container_get_children (GTK_CONTAINER (self->source_grid));
      for(l = children; l != NULL; l = g_list_next(l))
        gtk_container_remove (GTK_CONTAINER (self->source_grid), GTK_WIDGET (l->data));

      //TODO clear
    }

  self->item = g_object_ref (item);


  gtk_entry_set_text (GTK_ENTRY (self->title_entry), photos_base_item_get_name_with_fallback (item));

  item_id = photos_filterable_get_id (PHOTOS_FILTERABLE (item));
  PhotosFetchCollectionsJob *collection_fetcher = photos_fetch_collections_job_new (item_id);
  photos_fetch_collections_job_run (collection_fetcher,
                                    NULL,
                                    photos_properties_sidebar_on_collection_fetched,
                                    g_object_ref (self));
  g_object_unref (collection_fetcher);

  source_widget = photos_base_item_get_source_widget (item);
  gtk_widget_show (GTK_WIDGET (source_widget));
  gtk_container_add (GTK_CONTAINER(self->source_grid), source_widget);

}
