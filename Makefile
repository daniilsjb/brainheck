CC=gcc
CFLAGS=-O3 -Wall -Wextra -Werror

build: brainheck.c
	$(CC) brainheck.c -o brainheck $(CFLAGS)

clean:
	rm -f brainheck
