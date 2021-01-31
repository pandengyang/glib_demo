#include <stdio.h>
#include <glib.h>

/* GSourceMyIdle */
typedef struct GSourceMyIdle {
	GSource source;
} GSourceMyIdle;

gboolean g_source_myidle_prepare(GSource * source, gint * timeout);
gboolean g_source_myidle_check(GSource * source);
gboolean g_source_myidle_dispatch(GSource * source,
				  GSourceFunc callback,
				  gpointer user_data);
void g_source_myidle_finalize(GSource * source);

gboolean myidle(gchar * message);

int main(int argc, char *argv[])
{
	GMainLoop *loop = g_main_loop_new(NULL, FALSE);
	GMainContext *context = g_main_loop_get_context(loop);

	/* GSourceFuncs 包含一张函数表用于以通用的方式处理事件 */
	GSourceFuncs g_source_myidle_funcs = {
		g_source_myidle_prepare,
		g_source_myidle_check,
		g_source_myidle_dispatch,
		g_source_myidle_finalize,
	};

	/* 通过调用g_source_new 创建新事件源的实例，
	 * 创建时需传递新事件源结构体的大小和一张函数表，
	 * 而这张函数表决定了新事件源的行为
	 */
	GSource *source =
	    g_source_new(&g_source_myidle_funcs, sizeof(GSourceMyIdle));

	/* 设置 source 的回调函数 */
	g_source_set_callback(source, (GSourceFunc) myidle,
			      "KernelNewbies", NULL);

	/* 该 source 未与任何 GMainContext 关联
	 * 调用 g_source_attach 可将 source 和一个 GMainContext 关联起来
	 */
	g_source_attach(source, context);
	g_source_unref(source);

	g_main_loop_run(loop);

	g_main_context_unref(context);
	g_main_loop_unref(loop);

	return 0;
}

/* prepare 函数检查事件源是否有事件发生，
 * 如果已经有事件发生，则无需 poll
 */
gboolean g_source_myidle_prepare(GSource * source, gint * timeout)
{
	/* 使 poll 的超时为 0，不允许 poll 阻塞 */
	*timeout = 0;

	return TRUE;
}

/* check 函数检查事件源是否有事件发生 */
gboolean g_source_myidle_check(GSource * source)
{
	/* 每次检查 myidle 事件源，都有 myidle 事件发生
	 *
	 * 该示例中，prepare 返回 TRUE，check 返回 TRUE 或 FALSE 的结果是一样的
	 */
	// return FALSE;
	return TRUE;
}

/* 分发事件源的事件，实际就是调用事件源的回调函数 */
gboolean g_source_myidle_dispatch(GSource * source,
				  GSourceFunc callback, gpointer user_data)
{
	gboolean again;

	/* 如果未调用 g_source_set_callback 为该事件源设置回调函数
	 * callback 可能为 NULL
	 */
	if (!callback) {
		g_warning("no callback");

		return FALSE;
	}

	/* 当需要删除事件源时，dispatch 函数返回 G_SOURCE_REMOVE，
	 * 当需要保留事件源时，dispatch 函数返回 G_SOURCE_CONTINUE
	 *
	 * 根据回调函数的结果决定是否保留该事件源
	 */
	again = callback(user_data);

	return again;
}

/* source 被销毁前调用，做一些释放资源的工作 */
void g_source_myidle_finalize(GSource * source)
{
}

gboolean myidle(gchar * message)
{
	g_print("%s\n", message);

	/* 保留事件源 */
	// return G_SOURCE_CONTINUE;

	/* 删除事件源 */
	return G_SOURCE_REMOVE;
}
