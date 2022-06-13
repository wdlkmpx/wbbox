// This file is put in the public domain

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

struct wbbox_app
{
    const char *desc;
    int (*func) (int, char**);
};


struct wbbox_app apps[] =
{
    { "cddetect",       cddetect_main },
    { "cddetect_quick", cddetect_quick_main },
    { "debdb2pupdb",    debdb2pupdb_main },
    { "find_cat",       find_cat_main },
    { "vercmp",         vercmp_main },
    { NULL,             NULL },
};


int main (int argc, char **argv)
{
    int i;
    char *appname;
    appname = strrchr (argv[0], '/');
    if (appname) {
        appname++;
    } else {
        appname = argv[0];
    }

    for (i = 0; apps[i].desc; i++)
    {
        if (strcmp(appname,apps[i].desc) == 0) {
            return apps[i].func (argc, argv);
        }
    }

    printf ("Supported apps (symlinks):\n");
    for (i = 0; apps[i].desc; i++) {
        printf (" - %s\n", apps[i].desc);
    }
    return -1;
}
