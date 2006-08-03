/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy
  Copyright (C) 2006 Romain Lievin
  16/07/06 17:15 - menu.c

  This program is free software you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef __WIN32__
#include <direct.h> // _chdrive()
#endif

#include <stdio.h>
#include <gtk/gtk.h>
#include <glade/glade.h>

#include "file.h"
#include "gfm.h"
#include "menu.h"
#include "paths.h"

/* Change Drive Feature (Windows) */
#ifdef __WIN32__
static int windows_drive_change(char drive_letter)
{
	gchar *s;

    // Change drive and copy it.
    snprintf(settings.cur_dir, 8, "%c:\\", (char)drive_letter);
    s = g_strdup(settings.cur_dir);

    // Change Drive
	if (gfm_change_cwd(s) == -1)
	    msgbox_error("Could not change drive!");

    // Free String
	g_free(s);

    // Done
	return 0;
}

/* Change Drive Activator */
static void gfm_change_drive_activate(GtkMenuItem* menuitem, gpointer user_data)
{
	windows_drive_change((char)GPOINTER_TO_INT(user_data));

	// Refresh Folder Tree
	folder_tree_refresh();
}

static void set_drives(GtkWidget* widget, gpointer user_data)
{
	GtkWidget *menu = GTK_WIDGET(user_data);
	GtkWidget *change_drive;
	GtkWidget *change_drive_menu;
	GtkWidget *c_drive;
	int drive, curdrive;
	gchar buffer[8];
	gint available_drives[27];	// A..Z -> 26 letters

	change_drive = gtk_menu_item_new_with_label("Change drive");
	g_object_set_data_full(G_OBJECT(menu), "change_drive",
			       gtk_widget_ref(change_drive),
			       (GDestroyNotify)gtk_widget_unref);
	gtk_widget_show(change_drive);

	gtk_container_add(GTK_CONTAINER(menu), change_drive);
	change_drive_menu = gtk_menu_new();
	g_object_set_data_full(G_OBJECT(menu), "change_drive_menu",
			       gtk_widget_ref(change_drive_menu),
			       (GDestroyNotify)gtk_widget_unref);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(change_drive), change_drive_menu);

	curdrive = _getdrive();
	for (drive = 1; drive <= 26; drive++)
		available_drives[drive] = 0;

	for (drive = 3; drive <= 26; drive++)
	{
		if (!_chdrive(drive))
		{
			g_snprintf(buffer, 8, "%c:", drive + 'A' - 1);
			available_drives[drive] = drive + 'A' - 1;

			c_drive = gtk_menu_item_new_with_label(buffer);
			g_object_set_data_full(G_OBJECT(menu), "c_drive",
					       gtk_widget_ref(c_drive),
					       (GDestroyNotify)gtk_widget_unref);
			gtk_widget_show(c_drive);

			gtk_container_add(GTK_CONTAINER(change_drive_menu),
					  c_drive);
			g_signal_connect((gpointer)c_drive, "activate",
					   G_CALLBACK(gfm_change_drive_activate),
					   GINT_TO_POINTER(available_drives[drive]));
		}
	}
	_chdrive(curdrive);
}
#endif

/* Load Menu Function */
GtkWidget *create_folder_menu(void)
{
	GladeXML *xml;
	GtkWidget *menu;
	gpointer data;

	xml = glade_xml_new(gfm_paths_build_glade("gfm.glade"), "folder_menu", NULL);

	// Glade File Error
    if (!xml)
		g_error("GUI loading failed !\n");

	// Connect Signals
	glade_xml_signal_autoconnect(xml);

	// Activate the Items
	data = glade_xml_get_widget(xml, "show_all_files1");
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(data), settings.show_all);

	data = glade_xml_get_widget(xml, "confirm_delete/overwrite1");
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(data), settings.confirm);

    // Load the Menu Now
	menu = glade_xml_get_widget(xml, "folder_menu");

    // Drive Letters if we are a Windows User
    #ifdef __WIN32__
    set_drives(menu, menu);
    #endif

    // Return the Menu
	return menu;
}