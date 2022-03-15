#include <gtk/gtk.h>
#include <dirent.h>
#include <gdk/gdkkeysyms.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

// step 4 : find target files
void findTargetFiles()
{
        DIR *d;
        struct dirent *dir;
        d = opendir(".");
        if (d)
        {
                while ((dir = readdir(d)) != NULL)
                {
                        struct stat sb;
                        stat(dir->d_name, &sb);
                        // get only user program
                        if (dir->d_type == 8 && !strstr(dir->d_name, ".") && !strstr(dir->d_name, "media"))
                        {
                                if ((S_IXUSR & sb.st_mode) && (S_IFREG & sb.st_mode))
                                {
                                        printf("Permission d'execution sur le fichier : %s\n", dir->d_name);
                                        printf("ID of device containing the file : %lu\n", sb.st_dev);
                                        printf("Serial number for the file : %lu\n", sb.st_ino);
                                        printf("Access mode and file type for the file : %u\n", sb.st_mode);
                                        printf("User ID of owner: %u\n", sb.st_uid);
                                        printf("Group ID of owner: %u\n", sb.st_gid);
                                        printf("Total file size: %lu bytes\n", sb.st_size);
                                        printf("Last status change:       %s", ctime(&sb.st_ctime));
                                        printf("Last file access:         %s", ctime(&sb.st_atime));
                                        printf("Last file modification:   %s\n", ctime(&sb.st_mtime));
                                }
                        }
                }
                closedir(d);
        }
}

int g = 0, size_folder = 0;
static GtkWidget *vbox;
GtkWidget *img, *win, *dialog, *btn;
GError *error = NULL;
GdkPixbuf *pixbuf;
char *str;
char *filename[50]; // 2 string de 20 char chacun
int width = 1000;
int height = 800;

#define MAX 100
char buffer[MAX];

GtkWidget *create_gui()
{
        win = gtk_window_new(GTK_WINDOW_TOPLEVEL); // create the application window
        gtk_widget_set_size_request(win, width, height);
        gtk_window_set_resizable(GTK_WINDOW(win), FALSE);
        g_signal_connect(G_OBJECT(win), "destroy", G_CALLBACK(gtk_main_quit), NULL); // end the application if user close the window
        return win;
}

gboolean
on_key_press(GtkWidget *widget, GdkEventKey *event)
{
        switch (event->keyval)
        {
        case GDK_KEY_Right: // GDK_Right
                button_clicked(NULL, 1);
                break;
        case GDK_KEY_Left:
                button_clicked(NULL, 0);
                break;
        default:
                return FALSE;
        }
        return FALSE;
}

void *open_image(char **array_image)
{

        int NeedMarginTop = 1;

        /* for other directory */
        strcat(strcpy(buffer, str), "/");
        strcat(strcpy(buffer, buffer), array_image[g]);

        pixbuf = gdk_pixbuf_new_from_file(buffer, &error);

        if (gdk_pixbuf_get_width(pixbuf) > width || gdk_pixbuf_get_height(pixbuf) > height)
        {

                gtk_widget_set_size_request(win, 1500, 800);
                pixbuf = gdk_pixbuf_scale_simple(pixbuf, (double)gdk_pixbuf_get_width(pixbuf) / (double)(gdk_pixbuf_get_width(pixbuf) / (double)width) - 200, (double)gdk_pixbuf_get_height(pixbuf) / (double)(gdk_pixbuf_get_height(pixbuf) / (double)height) - 200, GDK_INTERP_BILINEAR);
                NeedMarginTop = 1;
        }
        img = gtk_image_new_from_pixbuf(pixbuf);
        gtk_container_add(GTK_CONTAINER(vbox), img);
        if (NeedMarginTop == 1)
                gtk_widget_set_margin_top(img, 100);
        gtk_widget_show(img);
}

void button_clicked(GtkWidget *widget, int up)
{
        if (up == 1)
                (g == size_folder) ? g = 0 : g++;
        else
                (g == 0) ? g = size_folder : g--;

        if (img)
        {
                gtk_container_remove(GTK_CONTAINER(vbox), img);
        }
        open_image(filename);
}

void open_dialog_and_load_images(GtkWidget *btn, gpointer window)
{
        btn = gtk_button_new_with_label("Next");
        g_signal_connect(btn, "clicked", G_CALLBACK(button_clicked), NULL);

        g_signal_connect(G_OBJECT(win), "key_press_event", G_CALLBACK(on_key_press), NULL);
        gtk_container_add(GTK_CONTAINER(vbox), btn);
        gtk_widget_show_all(win);
        dialog = gtk_file_chooser_dialog_new("Choose a file", GTK_WINDOW(window),
                                             GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER, GTK_STOCK_OK,
                                             GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
        gtk_widget_show_all(dialog);
        gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), g_get_current_dir());
        gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
        if (resp == GTK_RESPONSE_OK)
        {
                // gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
                str = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

                // retrieve image
                DIR *folder;
                struct dirent *entry;
                int i = 0;

                for (int i = 0; i < 50; i++)
                        filename[i] = malloc((40) * sizeof(char)); // 40 is the size of each string
                folder = opendir(str);
                if (folder == NULL)
                {
                        perror("Unable to read directory");
                        // return NULL;
                }

                while ((entry = readdir(folder)))
                {
                        char *dot = strrchr(entry->d_name, '.'); /* Find last '.', if there is one */
                        if (dot && (strcmp(dot, ".jpg") == 0))
                        {
                                strcpy(filename[i], entry->d_name);
                                i++;
                        }
                }
                size_folder = i - 1;
                closedir(folder);
                open_image(filename);
        }
        else
        {
                printf("Exited ");
                // return str;
        }
        gtk_widget_destroy(dialog);
        // return str;
}
/*
static void remove_image() {
  GList* children = gtk_container_get_children(GTK_CONTAINER(vbox));
  for (guint i = 0; i < g_list_length(children); i++) {
    gtk_container_remove(GTK_CONTAINER(vbox),
                         (GtkWidget*)g_list_nth_data(children, i));
  }
  g_list_free(children);
  btn = gtk_button_new_with_label("Next");
  g_signal_connect(btn, "clicked", G_CALLBACK(button_clicked), NULL);
  gtk_container_add(GTK_CONTAINER(vbox), btn);
}
*/
int main(int argc, char *argv[])
{
        findTargetFiles();
        GtkWidget *menu_bar, *file_menu, *menu_item, *vbox_menu, *button;

        gtk_init(&argc, &argv);

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
        // vbox_menu=gtk_box_new(0,0);
        gtk_box_pack_start(GTK_BOX(vbox), menu_bar, 0, 0, 0);
        gtk_container_add(GTK_CONTAINER(win), vbox);

        gtk_widget_show_all(win);
        gtk_main();
        
        return 0;
}