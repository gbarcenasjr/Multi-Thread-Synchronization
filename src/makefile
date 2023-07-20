CC      = gcc
LFLAGS  = -L. 
LIBS    = -lm
CFLAGS  = -g -O2
INCS    = -I.

SRCS	= project.c 
EXEC    = project.exe
#               sleep nprod ncons
RUN_CMD	=./$(EXEC) 25    1     1
OBJS	=$(SRCS:%.c=%.o)

all: clean $(EXEC) run


$(EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LFLAGS) $(LIBS)

%.o : %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

run: $(EXEC)
	$(RUN_CMD)

clean:
	rm -f $(EXEC) $(OBJS) *~

.PHONY: clean run all
