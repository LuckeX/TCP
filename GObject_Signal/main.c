#include "signal-demo.h"

//static void
//my_signal_handler (gpointer *p)
//{
//     g_print("%s",(gchar*)p);
////    gint *t = (gint*)p;
////    g_print("%d",*t);
////    Port *port = (Port*)userdata;
////    g_print("this is my_signal_handler\n");
////    g_print ("my_signal_handler said: %s\n", buffer);
//////    g_print ("my_signal_handler said: %s\n", (gchar*)userdata);
//
//}

static void
my_signal_handler (gpointer *instance, gchar *buffer, gpointer userdata)
{
//    g_print ("my_signal_handler said: %s\n", buffer);
    g_print ("my_signal_handler said: %s\n", (gchar *)userdata);
}

int
main (void)
{
    gchar *ptr = "hello";
    gchar *userdata = "This is userdata";
    SignalDemo *sd_obj = g_object_new (SIGNAL_TYPE_DEMO, NULL);

    /* 信号连接 */
    // g_signal_connect (sd_obj, "hello",
    //                   G_CALLBACK (my_signal_handler),
    //                   userdata);

    /* 发射信号 */
    int a=0;
    g_signal_emit_by_name (sd_obj,
                           "hello",
                           1,2,
                           &a);
    g_print("signal return value: %d\n",a);

    return 0;
}
