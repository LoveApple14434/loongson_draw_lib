CROSS_PREFIX = loongarch64-linux-gnu-
CC = $(CROSS_PREFIX)gcc
AR = $(CROSS_PREFIX)ar
CXX = $(CROSS_PREFIX)g++
SRCS = draw_basic.cpp draw_higher.cpp draw_bmp.cpp
HDRS = draw.hpp
OUTDIR = build
OUTDIR_UPPER = build_upper  # 上位机构建目录

CXXFLAGS = -O2 -fPIC -I.
ARFLAGS = rcs

OBJS = $(patsubst %.cpp,$(OUTDIR)/%.o,$(SRCS))
LIB = $(OUTDIR)/libdraw.a

# 上位机工具链和文件
UPPER_CXX = g++
UPPER_OBJS = $(patsubst %.cpp,$(OUTDIR_UPPER)/%.o,$(SRCS))
UPPER_LIB = $(OUTDIR_UPPER)/libdraw.a

NFS4 = /srv/nfs4/loveapple
INSTALL_DIR = $(NFS4)/lib

.PHONY: all clean install upper upper_clean

all: $(LIB)

$(OUTDIR):
	mkdir -p $(OUTDIR)

$(OUTDIR_UPPER):
	mkdir -p $(OUTDIR_UPPER)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

$(OUTDIR)/%.o: %.cpp $(HDRS) | $(OUTDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 上位机目标
upper: $(UPPER_LIB)

$(UPPER_LIB): $(UPPER_OBJS)
	$(AR) $(ARFLAGS) $@ $(UPPER_OBJS)

# 修复：显式定义每个上位机目标文件的规则
$(OUTDIR_UPPER)/draw_basic.o: draw_basic.cpp $(HDRS) | $(OUTDIR_UPPER)
	$(UPPER_CXX) $(CXXFLAGS) -c $< -o $@

$(OUTDIR_UPPER)/draw_higher.o: draw_higher.cpp $(HDRS) | $(OUTDIR_UPPER)
	$(UPPER_CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OUTDIR)

upper_clean:
	rm -rf $(OUTDIR_UPPER)

install:
	mkdir -p $(INSTALL_DIR)
	cp $(LIB) $(INSTALL_DIR)/