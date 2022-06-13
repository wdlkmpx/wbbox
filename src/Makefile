include ../config.mk

APP  = wbbox
# ls *.c | sed "s%\.c%.o%g" | tr "\n" " " >> Makefile
OBJS = cddetect.o cddetect_quick.o debdb2pupdb.o find_cat.o hotplug2stdout.o main.o vercmp.o 

LINKS = cddetect cddetect_quick debdb2pupdb find_cat hotplug2stdout vercmp

#CPPFLAGS += -I..
CFLAGS += -I..
LIBS   += 

all: $(APP)

$(APP): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(APP) $(LDFLAGS) $(LIBS)
	@for i in $(LINKS) ; do \
		[ ! -e $${i} ] && ln -sv wbbox $${i} || true; \
	done

strip: $(APP)
	$(STRIP) $(APP)

distclean: clean

clean:
	rm -f *.a *.o *.so *~ $(APP) $(LINKS)

install: $(APP)
	mkdir -p $(DESTDIR)$(bindir)
	install -c $(APP) $(DESTDIR)$(bindir)
	cp -a $(LINKS) $(DESTDIR)$(bindir)

install-strip: strip install

uninstall:
	rm -f $(DESTDIR)$(bindir)/$(APP)

