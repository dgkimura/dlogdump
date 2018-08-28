VERSION_STR="0.6devel"

PROGRAM = dlogdump
OBJS    = dlogdump.o

PG_CPPFLAGS = -DVERSION_STR=\"$(VERSION_STR)\" -I. -I$(libpq_srcdir) -DDATADIR=\"$(datadir)\"
PG_LIBS = $(libpq_pgport)

ifdef USE_PGXS
PGXS := $(shell pg_config --pgxs)
include $(PGXS)
else
subdir = contrib/dlogdump
top_builddir = ../..
include $(top_builddir)/src/Makefile.global
include $(top_srcdir)/contrib/contrib-global.mk
endif

majorversion=`echo $(PG_VERSION) | sed -e 's/^\([0-9]*\)\.\([0-9]*\).*/\1\2/g'`
