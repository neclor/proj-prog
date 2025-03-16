/**
 * @file main.c
 * @author: Pavlov Aleksandr s2400691
 * @date: 24.03.2025
 * @brief Main file
*/

#include <stdlib.h>
#include <gtk/gtk.h>


void on_button_clicked(GtkWidget *widget, gpointer data) {
   g_print("Кнопка нажата!\n");
}

int main(int argc, char *argv[]) {
   gtk_init(&argc, &argv);

   GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

   gtk_window_set_title(GTK_WINDOW(window), "GTK2 Пример");


   gtk_container_set_border_width(GTK_CONTAINER(window), 100);

   g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

   GtkWidget *button = gtk_button_new_with_label("Нажми меня");
   g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
   gtk_container_add(GTK_CONTAINER(window), button);

   gtk_widget_show_all(window);
   gtk_main();

   printf("abc");

   return 0;
}
