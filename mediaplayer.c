#include <gtk/gtk.h>

#include <dirent.h>

#include <gdk/gdkkeysyms.h>

#include <stdlib.h>

#include <stdio.h>

int g = 0, size_folder = 0;
static GtkWidget * vbox;
GtkWidget * img;
char * str;
char * filename[50]; // 2 string de 20 char chacun
/*
static void remove_image() {
  GList* children = gtk_container_get_children(GTK_CONTAINER(vbox));
  for (guint i = 0; i < g_list_length(children); i++) {
    gtk_container_remove(GTK_CONTAINER(vbox),
                         (GtkWidget*)g_list_nth_data(children, i));
  }
  g_list_free(children);
}
*/

GtkWidget * create_gui() {
        GtkWidget * win = gtk_window_new(GTK_WINDOW_TOPLEVEL); // create the application window
        g_signal_connect(G_OBJECT(win), "destroy", G_CALLBACK(gtk_main_quit), NULL); // end the application if user close the window
        return win;
}

gboolean
on_key_press(GtkWidget * widget, GdkEventKey * event) {
        switch (event -> keyval) {
        case GDK_KEY_Right: // GDK_Right
                printf("key pressed: %s\n", ">");
                break;
        default:
                return FALSE;
        }
        return FALSE;
}

void * open_image(char ** array_image) {
        /*
        	for(int i =0; i <  50; i++) {
        		printf("%s", array_image[i]);
        	}
        	*/
        img = gtk_image_new_from_file(array_image[g]); // image shall be in the same dir 
        gtk_container_add(GTK_CONTAINER(vbox), img);
        gtk_widget_show(img);

}

void button_clicked(GtkWidget * widget) {
        //printf("g : %d\n", g);
        (g == size_folder) ? g = 0: g++;

        if (img) {
                gtk_container_remove(GTK_CONTAINER(vbox), img);
        }
        open_image(filename);
}

void open_dialog_and_load_images(GtkWidget * btn, gpointer window) {
        GtkWidget * dialog;
        dialog = gtk_file_chooser_dialog_new("Choose a file", GTK_WINDOW(window),
                GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER, GTK_STOCK_OK,
                GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
        gtk_widget_show_all(dialog);
        gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), g_get_current_dir());
        gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
        if (resp == GTK_RESPONSE_OK) {
                //gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
                str = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

                // retrieve imùage
                DIR * folder;
                struct dirent * entry;
                int i = 0;

                for (int i = 0; i < 50; i++)
                        filename[i] = malloc((40) * sizeof(char)); // 40 is the size of each string
                //printf("%s", str);
                folder = opendir(str);
                if (folder == NULL) {
                        perror("Unable to read directory");
                        //return NULL;
                }

                while ((entry = readdir(folder))) {
                        char * dot = strrchr(entry -> d_name, '.'); /* Find last '.', if there is one */
                        if (dot && (strcmp(dot, ".jpg") == 0)) {
                                strcpy(filename[i], entry -> d_name);
                                i++;
                        }
                }
                size_folder = i - 1;
                closedir(folder);
                open_image(filename);
                /*
                for(int j =0; j<i;j++) {
                	printf("%s\n", filename[j]);
                }
                */

        } else {
                printf("Exited ");
                //return str;
        }
        gtk_widget_destroy(dialog);
        //return str;
}

int main(int argc, char * argv[]) {

        GtkWidget * win, * btn, * menu_bar, * file_menu, * menu_item, * vbox_menu, * button;

        //char ** array_image = open_all_images_in_directory();

        gtk_init( & argc, & argv);

        win = create_gui();

        menu_bar = gtk_menu_bar_new();

        file_menu = gtk_menu_new();
        menu_item = gtk_menu_item_new_with_label("File");
        gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), file_menu);
        gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item);

        menu_item = gtk_menu_item_new_with_label("Open");
        gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), menu_item);
        g_signal_connect(menu_item, "activate", G_CALLBACK(open_dialog_and_load_images), win);

        vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        //vbox_menu=gtk_box_new(0,0);
        gtk_box_pack_start(GTK_BOX(vbox), menu_bar, 0, 0, 0);
        gtk_container_add(GTK_CONTAINER(win), vbox);

        //open_image(array_image, vbox);
        //g_signal_connect(G_OBJECT(win), "key_press_event", G_CALLBACK(on_key_press), NULL);
        btn = gtk_button_new_with_label("Next");
        g_signal_connect(btn, "clicked", G_CALLBACK(button_clicked), NULL);
        gtk_container_add(GTK_CONTAINER(vbox), btn);

        gtk_widget_show_all(win);
        gtk_main();

        return 0;
}
