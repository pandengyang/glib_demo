CC = gcc
CPPFLAGS = -I./include
CFLAGS = `pkg-config --cflags glib-2.0`
LDFLAGS = 
LIBS = `pkg-config --libs glib-2.0`

RM = rm -rf
MKDIR = mkdir -p
SED = sed

TARGET = demo

DEP_DIR = .dep

SRCS = 
OBJS = 
DEP_DIRS = $(DEP_DIR)

sinclude hello/subdir.mk
sinclude eat/subdir.mk

SRCS += $(wildcard *.c)
OBJS += $(patsubst %.c, %.o, $(SRCS))

TARGET:$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS) $(LIBS)

$(OBJS):%.o:%.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $<

sinclude $(patsubst %.c, $(DEP_DIR)/%.d, $(SRCS))
$(DEP_DIR)/%.d:%.c
	-$(MKDIR) $(DEP_DIRS); \
	$(RM) $@; \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	$(SED) 's,\($*\)\.o[: ]*,\1.o $@: ,g' < $@.$$$$ > $@; \
	$(RM) $@.$$$$

.PHONY:fmt clean cleanall

fmt:
	find . -name "*.c" | xargs -I {} indent -kr -i8 {} -o {}

clean:
	-$(RM) $(TARGET) $(OBJS)

cleanall:
	-$(RM) $(TARGET) $(OBJS) $(DEP_DIR) .*.sw?

