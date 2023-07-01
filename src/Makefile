include ../config.mk

APP  = wbbox$(EXE)

OBJS = find_cat.o main.o vercmp.o 
LINKS = find_cat$(EXE) vercmp$(EXE)

ifeq ($(TARGET_OS),Linux) 
OBJS += debdb2pupdb.o cddetect.o cddetect_quick.o hotplug2stdout.o
LINKS += debdb2pupdb$(EXE) cddetect$(EXE) cddetect_quick$(EXE) hotplug2stdout$(EXE)
endif

SLINK_CMD = ln -sv
ifdef EXE
SLINK_CMD = cp -afv
endif

#CPPFLAGS += -I..
CFLAGS += -I..
LIBS   += 

all: $(APP)

$(APP): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(APP) $(LDFLAGS) $(LIBS)
	@for i in $(LINKS) ; do \
		[ ! -e $${i} ] && $(SLINK_CMD) $(APP) $${i} || true; \
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

