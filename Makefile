CFLAGS := \
	-g \
	-O0

LDFLAGS := \
	-lncurses \
	-lpanel \
	-lmenu


# 获取当前正在执行的makefile的绝对路径
MKP := $(abspath $(lastword $(MAKEFILE_LIST)))
# 根文件夹
RDIR := $(shell dirname $(MKP))
# 代码文件夹
SDIR := $(RDIR)/src
# 可执行程序文件夹
BDIR := $(RDIR)/bin

# C代码文件
SRCS := $(wildcard $(SDIR)/*.c)
EXES := $(patsubst $(SDIR)/%.c, $(BDIR)/%, $(SRCS))

.PHONY: echo
echo:
	@echo $(MKP)
	@echo $(RDIR)
	@echo $(BDIR)

.PHONY: mkdir
mkdir:
	@mkdir -p $(SDIR)
	@mkdir -p $(BDIR)

.PHONY: clean
clean:
	@rm -rf $(BDIR)

.DEFAULT_GOAL := all
all: mkdir $(EXES)

$(EXES): $(BDIR)/%: $(SDIR)/%.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)