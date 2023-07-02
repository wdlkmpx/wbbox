
#ifndef __WBBOX_MAIN_H
#define __WBBOX_MAIN_H 1

#ifdef __linux__
int cddetect_main (int argc, char **argv);
int cddetect_quick_main (int argc, char **argv);
int hotplug2stdout_main(int argc, char **argv);
int debdb2pupdb_main (int argc, char **argv);
#endif
int vercmp_main (int argc, char **argv);

#endif