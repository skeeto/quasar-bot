CFLAGS = -std=c99 -Wall -g3
LDLIBS = -lgdi32

biocheat.exe : biocheat.c
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

run : biocheat.exe
	./$^

clean :
	del biocheat.exe
