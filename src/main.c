// Public Domain

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

#ifdef _MSC_VER
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#endif


struct wbbox_app
{
	const char *desc;
	int (*func) (int, char**);
};

struct wbbox_app apps[] =
{
#ifdef __linux__
	{ "cddetect",       cddetect_main },
	{ "cddetect_quick", cddetect_quick_main },
	{ "hotplug2stdout", hotplug2stdout_main },
	{ "debdb2pupdb",    debdb2pupdb_main },
#endif
	{ "find_cat",       find_cat_main },
	{ "vercmp",         vercmp_main },
	{ NULL,             NULL },
};


int main (int argc, char **argv)
{
	int i;
	char *appname;
	appname = strrchr (argv[0], '/');
#if defined(_WIN32) || defined(__CYGWIN__) || defined(MSDOS)
	if (!appname) {
		appname = strrchr (argv[0], '\\');
	}
	char *p = strrchr (argv[0], '.');
	if (p && strcasecmp(p,".exe") == 0) {
		*p = '\0'; //remove .exe
	}
#endif
	if (appname) {
		appname++;
	} else {
		appname = argv[0];
	}

	for (i = 0; apps[i].desc; i++)
	{
		if (strcasecmp(appname,apps[i].desc) == 0) {
			return apps[i].func (argc, argv);
		}
	}

	if (argc > 1)
	{
		argv++;
		appname = argv[0];
		for (i = 0; apps[i].desc; i++) {
			if (strcasecmp(appname,apps[i].desc) == 0) {
				return apps[i].func (argc-1, argv);
			}
		}
	}

	printf ("Supported apps (symlinks):\n");
	for (i = 0; apps[i].desc; i++) {
		printf (" - %s\n", apps[i].desc);
	}
	return -1;
}
