CROSS_PREFIX = loongarch64-linux-gnu-
CC = $(CROSS_PREFIX)gcc
AR = $(CROSS_PREFIX)ar
CXX = $(CROSS_PREFIX)g++
SRCS = draw_basic.cpp draw_higher.cpp
HDRS = draw.h
OUTDIR = build

CXXFLAGS = -O2 -fPIC -I.
ARFLAGS = rcs

OBJS = $(patsubst %.cpp,$(OUTDIR)/%.o,$(SRCS))
LIB = $(OUTDIR)/libdraw.a

NFS4 = /srv/nfs4/loveapple
INSTALL_DIR = $(NFS4)/lib

.PHONY: all clean
all: $(LIB)

$(OUTDIR):
	mkdir -p $(OUTDIR)

$(LIB): $(OUTDIR) $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

$(OUTDIR)/%.o: %.cpp $(HDRS) | $(OUTDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OUTDIR)

install:
	mkdir -p $(INSTALL_DIR)
	cp $(LIB) $(INSTALL_DIR)/