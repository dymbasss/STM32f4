BUILD_HOME = ../../..

include $(BUILD_HOME)/src/Makefile.include

NAME = pwm
LIB_A = lib$(NAME).a

all: $(LIB_A) lib-copy

SRC = pwm.c
OBJS = ${SRC:.c=.o}

$(LIB_A): $(OBJS)
	$(AR) r $@ $(OBJS)

lib-copy: $(LIB_A)
	cp -f $(LIB_A) $(BUILD_HOME)/src/ws_example_№5/lib_all

