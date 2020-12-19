#include <stdio.h>
#include <glib.h>

/* timeout functions */
gboolean count_down(gpointer data);
gboolean cancel_fire(gpointer data);

/* idle functions */
gboolean say_idle(gpointer data);

int main(int argc, char *argv[])
{
	GMainLoop *loop = g_main_loop_new(NULL, FALSE);

	g_timeout_add(500, count_down, NULL);
	g_timeout_add(8000, cancel_fire, loop);

	g_idle_add(say_idle, NULL);

	g_main_loop_run(loop);

	return 0;
}

/* timeout functions */
gboolean count_down(gpointer data)
{
	static int counter = 10;

	if (counter < 1) {
		printf("-----[FIRE]-----\n");

		return FALSE;
	}

	printf("-----[% 4d]-----\n", counter--);

	return TRUE;
}

gboolean cancel_fire(gpointer data)
{
	GMainLoop *loop = data;

	printf("-----[QUIT]-----\n");
	g_main_loop_quit(loop);

	return FALSE;
}

/* idle functions */
gboolean say_idle(gpointer data)
{
	printf("-----[IDLE]-----\n");

	// return TRUE;
	return FALSE;
}
