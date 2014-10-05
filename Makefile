CFLAGS = -std=c99 -Wall
LDLIBS = -lgdi32 -lws2_32

biocheat.exe : biocheat.c
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

run : biocheat.exe
	./$^

clean :
	del biocheat.exe
