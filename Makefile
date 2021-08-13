NAME = hackbox
CC = cc
SRCS = $(wildcard *.c)
SRCS += $(wildcard utils/*.c)
OBJS = $(SRCS:%.c=%.o)
CFLAGS = -c -g
RM = rm -f

all: $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clear:
	$(RM) $(OBJS) $(NAME)

