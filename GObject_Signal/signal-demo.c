//
// Created by xyk on 19-6-29.
//

#include "signal-demo.h"


G_DEFINE_TYPE (SignalDemo, signal_demo, G_TYPE_OBJECT);

static void
signal_demo_default_handler (gpointer instance, gpointer t, gpointer userdata)
{
//    Port *p = (Port*)port;
//    g_print("min:%d, max: %d\n",p->min,p->max);
//    p->actual = (p->min+p->max)/2;
//    g_print("the actual port is %d\n",p->actual);
//      g_print("p is %d",p);
//     g_print("%s\n",buffer);
      g_print("min port is %s\n",(char*)t);
}

void
signal_demo_init (SignalDemo *self)
{
}

void
signal_demo_class_init (SignalDemoClass *klass)
{
    klass->default_handler = signal_demo_default_handler;

    g_signal_new ("hello",
                  G_TYPE_FROM_CLASS (klass),
                  G_SIGNAL_RUN_FIRST,
                  G_STRUCT_OFFSET (SignalDemoClass, default_handler),
                  NULL,
                  NULL,
                  g_cclosure_marshal_VOID__STRING,
                  G_TYPE_NONE,
                  1,
                  G_TYPE_STRING);
}