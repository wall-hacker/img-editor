# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS=image_editor

build: $(TARGETS)

image_editor: image_editor.c apply.h crop.h image.h load.h rotate.h save.h select.h utils.h
	$(CC) $(CFLAGS) image_editor.c -o image_editor apply.c crop.c load.c rotate.c save.c -lm select.c utils.c

pack:
	zip -FSr 311CA_AndreiCalinMihail_Tema2.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
