#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <linux/types.h>
#include <linux/netlink.h>

static void die(char *s) {
	fprintf(stderr, "%s", s);
	exit(1);
}

int hotplug2stdout_main(int argc, char **argv)
{
	struct sockaddr_nl nls;
	struct pollfd pfd;
	char buf[512];

	// Open hotplug event netlink socket

	memset(&nls,0,sizeof(struct sockaddr_nl));
	nls.nl_family = AF_NETLINK;
	nls.nl_pid = getpid();
	nls.nl_groups = -1;

	pfd.events = POLLIN;
	pfd.fd = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_KOBJECT_UEVENT);
	if (pfd.fd == -1) {
		die("Not root\n");
	}
	// Listen to netlink socket
	if (bind(pfd.fd, (void *)&nls, sizeof(struct sockaddr_nl))) {
		die("Bind failed\n");
	}
	while (-1 != poll(&pfd, 1, -1)) {
		int len = recv(pfd.fd, buf, sizeof(buf), MSG_DONTWAIT);
		if (len == -1) die("recv\n");
		printf("%s\n", buf); //ME Print only once
		/* ME It seems that some data is being buffered for some reason.
		 * Flush the stdout buffer to push it along to where we need it*/
		fflush(stdout); 
	}
	die("poll\n");
	return 0;
}
