/* 
 * big parts taken from cdfs (C) 1999, 2000, 2001 by Michiel Ronsse
 * relesed under the GPL v.2
 * more parts taken from isoinfo/isodump (W) 1993 Eric Youngdale,
 * (C) 1993 Yggdrasil Computing, Incorporated, also released
 * under the GPL v.2
 *
 * Cut down for fast detection if disc inserted only. BK may 2008
 */

#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <linux/cdrom.h>

#define DDEV "/dev/sr0"
char *device = DDEV;

static void usage(const char *progname)
{
	fprintf(stderr,"usage: cddetect_quick -d/dev/sr0\n");
	fprintf(stderr,"       returns 0 if disc is inserted\n");
	exit(0);
}

int cddetect_quick_main(int argc, char **argv)
{
	int fd, status, optchar;

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-d") == 0) {
			i++;
			if (i < argc) {
				device = argv[i];
			}
		} else if (argv[i][0] == '-' && argv[i][1] == 'd') {
			if (strlen(argv[i]) > 2) {
				device = argv[i]+2;
			}
		} else {
			usage(argv[0]);
		}
	}

	fd = open(device, O_RDONLY | O_NONBLOCK);
	if (fd < 0) {
		printf("cannot open %s\n", device);
		exit(-1);
	}

	// read the drive status info
	status = ioctl(fd, CDROM_DRIVE_STATUS, CDSL_CURRENT);

	// CDS_NO_INFO: function not implemented
	switch(status) {
		case CDS_NO_DISC: printf("no disc\n"); break ;
		case CDS_TRAY_OPEN: printf("tray open\n"); break ;
		case CDS_DRIVE_NOT_READY: printf("drive not ready\n"); break ;
		case CDS_DISC_OK:
			close(fd);
			printf("disc inserted\n");
			return 0;
			break;
		default: // unidentified problem
			printf("unidentified error\n");
			break;
	}
	close(fd);
	return -1;
}
