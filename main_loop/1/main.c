#include <stdio.h>
#include <glib.h>

/* timeout functions */
gboolean count_down(gpointer data);
gboolean cancel_fire(gpointer data);

/* idle functions */
gboolean say_idle(gpointer data);

int main(int argc, char *argv[])
{
	/* GMainLoop表示一个主事件循环，由g_main_loop_new创建 */
	GMainLoop *loop = g_main_loop_new(NULL, FALSE);

	/* 添加超时事件源 */
	g_timeout_add(500, count_down, NULL);
	g_timeout_add(8000, cancel_fire, loop);

	/* 添加空闲函数，当没有更高优先级的事件时，
	 * 空闲函数就会被执行
	 */
	g_idle_add(say_idle, NULL);

	/* 该函数将不停地检查事件源中是否有新事件进行分发
	 *
	 * 在某事件处理函数中调用 g_main_loop_quit 将导致
	 * 该函数退出
	 */
	g_main_loop_run(loop);

	return 0;
}

/* 超时事件处理函数 */
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

/* 超时事件处理函数 */
gboolean cancel_fire(gpointer data)
{
	GMainLoop *loop = data;

	printf("-----[QUIT]-----\n");
	/* 退出主循环，g_main_loop_run 返回 */
	g_main_loop_quit(loop);

	return FALSE;
}

/* 空闲函数 */
gboolean say_idle(gpointer data)
{
	printf("-----[IDLE]-----\n");

	// return TRUE;
	return FALSE;
}
