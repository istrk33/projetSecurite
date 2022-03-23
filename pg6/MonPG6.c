#include <gtk/gtk.h>

#include <gdk/gdkkeysyms.h>

#include <stdlib.h>

#include <stdio.h>

#include <time.h>

// gcc -o MonPG6 pg6/MonPG6.c `pkg-config --cflags --libs gtk+-3.0`

GtkWidget *label, *win, *vbox, *btn_start, *btn_reset, *hbox, *btn_checkpoint;
GtkStyleContext *context;

int counterCheckpoint = 1;

static gboolean continue_timer = FALSE;

int nouveauParagraphe = 1;

int h, m, s;

int reset= 0;

char seconds[9];
char minutes[9];
char hours[9];

char chronoTime[30];
char buf[256];
char buff[30];

/*
 * Function: start_time 
 * launch the timer
 */
 
void start_time() {
	continue_timer=!continue_timer;
	
	while(continue_timer) {
	s++;
	sleep(1); // environs 1 seconde
	if (s==60) {
			m++;
			s=0;		
		}
		
	if (m==60) {
			m=0;
			h++;
		}
		
		// 02d permet un affichage plus propre : 9 => 09
		
		/* conversion entier -> string */
		sprintf(seconds, "%02d", s);
		sprintf(minutes, "%02d", m);
		sprintf(hours, "%02d", h);
		
		/* on concatene le tout */
		strcat(chronoTime,hours);
		strcat(chronoTime,":");
		strcat(chronoTime,minutes);	
		strcat(chronoTime,":");
		strcat(chronoTime,seconds);	
		
		/* update le texte */
		gtk_label_set_text(GTK_LABEL(label), chronoTime);
	  memset(chronoTime, 0, 1);

		gtk_widget_show(label);
		
		/* necessaire pour un affichage dynamique */
		while(g_main_context_iteration(NULL,FALSE))
			gtk_main_iteration();

	}
}

/*
 * Function: reset_timer 
 * reset the timer to 00:00:00 and stop the run
 */
 
void reset_timer() {
    continue_timer=FALSE;
    h=0, m =0 , s=0;
    gtk_label_set_text(GTK_LABEL(label), "00:00:00");
}

/*
 * Function: save_timer 
 * save the actual timing to a file called checkpoint 
 */
 
void save_timer() {
	FILE * filePointer;
	
	filePointer = fopen("./checkpoint.txt", "a");
	
		if (filePointer==NULL) {
		perror("fopen\n");
		return ;
	} 
		
		sprintf(seconds, "%02d", s-1);
		sprintf(minutes, "%02d", m);
		sprintf(hours, "%02d", h);
		
		sprintf(buff, "Checkpoint numero %d : ", counterCheckpoint);
		
		counterCheckpoint++;
		
		strcat(buf, buff);
		strcat(buf,hours);
		strcat(buf,":");
		strcat(buf,minutes);	
		strcat(buf,":");
		strcat(buf,seconds);	
	
	/* si c'est le premier checkpoint du programme, on separe les 
	lignes du .txt des anciennes executions avec la nouvelle */
	
	if(nouveauParagraphe==1) {
		char paragraphe[] = "------------------------------\n";
		fputs(paragraphe, filePointer);
		nouveauParagraphe=0;
	}
	
	fputs(buf, filePointer);
	fputs("\n", filePointer);
	fflush(stdout);
	memset(buf, 0, 256);

	fclose(filePointer);
	
}

int main(int argc, char * argv[]) {
	
	gtk_init( & argc, & argv);
	
  win = gtk_window_new(GTK_WINDOW_TOPLEVEL); // create the application window
  g_signal_connect(G_OBJECT(win), "destroy", G_CALLBACK(gtk_main_quit), NULL); // end the application if user close the window
	
	/* minimal size of the window and forbid the resizing */
	gtk_widget_set_size_request(win, 500, 110);
	gtk_window_set_resizable (GTK_WINDOW(win), FALSE);

	label = gtk_label_new("00:00:00");
	
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	
	btn_start = gtk_button_new_with_label("START");
	g_signal_connect(btn_start, "clicked", G_CALLBACK(start_time), NULL);
	
	btn_reset = gtk_button_new_with_label("RESET");
	g_signal_connect(btn_reset, "clicked", G_CALLBACK(reset_timer), NULL);
	
	btn_checkpoint = gtk_button_new_with_label("SAVE");
	g_signal_connect(btn_checkpoint, "clicked", G_CALLBACK(save_timer), NULL);
	
	gtk_widget_set_halign(btn_reset, GTK_ALIGN_END);
	gtk_widget_set_halign(btn_start, GTK_ALIGN_END);

  gtk_container_add(GTK_CONTAINER(win), vbox);
  gtk_container_add(GTK_CONTAINER(vbox), label);
  gtk_container_add(GTK_CONTAINER(vbox), hbox);
  
  gtk_box_pack_start (GTK_BOX (hbox), btn_start, 0, 0, 0);
  gtk_box_pack_start (GTK_BOX (hbox), btn_reset, 0, 0, 0);
  gtk_box_pack_start (GTK_BOX (hbox), btn_checkpoint, 0, 0, 0);
  
  GtkCssProvider *cssProvider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(cssProvider, "./pg6/theme.css", NULL);
  gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                               GTK_STYLE_PROVIDER(cssProvider),
                               GTK_STYLE_PROVIDER_PRIORITY_USER);
                               
   /* apply css */                     
   context = gtk_widget_get_style_context(btn_start);
	 gtk_style_context_add_class(context,"btn_start");
	 
  context = gtk_widget_get_style_context(label);
	gtk_style_context_add_class(context,"label");
	
	context = gtk_widget_get_style_context(btn_checkpoint);
	gtk_style_context_add_class(context,"btn_checkpoint");
	 
  gtk_widget_show_all(win);

  gtk_main();

  return 0;
        
}
