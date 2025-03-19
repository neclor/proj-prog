#include <gtk/gtk.h>
#include <cairo.h>
#include <stdbool.h>
#include <stdio.h>

// Функция для рисования (GTK2 использует expose-event)
static gboolean expose_event_callback(GtkWidget *widget, GdkEventExpose *event, gpointer data) {
    // Создаем контекст Cairo
    cairo_t *cr = gdk_cairo_create(widget->window);

    // Получаем текущий размер окна
    GtkAllocation allocation;
    gtk_widget_get_allocation(widget, &allocation);
    int width = allocation.width;
    int height = allocation.height;

    // Устанавливаем масштабирование
    cairo_scale(cr, (double)width / 800, (double)height / 600);

    // Clear the background
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);

    // Рисуем PNG-изображение
    cairo_surface_t *image = cairo_image_surface_create_from_png("path/to/your/image.png");
    cairo_set_source_surface(cr, image, 100, 100); // Координаты (100, 100)
    cairo_paint(cr);
    cairo_surface_destroy(image);

    // Рисуем красный круг
    static int a = 0;
    static int b = 1;
    b++;
    if (b < 500) return FALSE;
    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_arc(cr, a++, a++, 50, 0, 2 * G_PI);
    cairo_fill(cr);

    cairo_destroy(cr);
    return FALSE;
}

// Функция игрового цикла
static gboolean custom_loop(gpointer data) {
    GtkWidget *widget = GTK_WIDGET(data);
    gtk_widget_queue_draw(widget); // Trigger redraw
    return TRUE; // Continue the loop
}

static guint timeout_id = 0; // Store the timeout ID

// Функция для удаления пользовательского цикла
static void remove_custom_loop() {
    if (timeout_id != 0) {
        g_source_remove(timeout_id);
        timeout_id = 0;
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    printf("edasdasda");

    printf("GTK version: %d.%d.%d\n", gtk_get_major_version(), gtk_get_minor_version(), gtk_get_micro_version());

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Red Circle");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    // Создаем GtkDrawingArea
    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, 300, 300);
    gtk_container_add(GTK_CONTAINER(window), drawing_area);

    // Подключаем сигнал "expose-event" к drawing_area (для GTK2)
    g_signal_connect(G_OBJECT(drawing_area), "expose-event", G_CALLBACK(expose_event_callback), NULL);

    // Подключаем сигнал "destroy" к окну
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Убедитесь, что виджеты отображаются перед запуском цикла
    gtk_widget_show_all(window);

    // Запускаем пользовательский цикл
    timeout_id = g_timeout_add(16, custom_loop, drawing_area); // ~60 FPS

    // Пример: Удаляем цикл через 5 секунд
    g_timeout_add_seconds(5, (GSourceFunc)remove_custom_loop, NULL);

    gtk_main();

    return 0;
}
