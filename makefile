CC = gcc
CFLAGS += -Wall
CCFLAG += -g
CCFLAGS += -c
DLL_LIB :=
# DLL_LIB = -lmingw32
# DLL_LIB += -llibwinmm
DLL_LIB += -lSDL2main
DLL_LIB += -lSDL2
DLL_LIB += -lSDL2_mixer
DLL_LIB += -lSDL2_image
DLL_LIB += -ltmx
DLL_LIB += -lxml2
DLL_LIB += -lz
#DLL_LIB += -liconv
#DLL_LIB += -lwsock32
INCLUDE_PATH += $(addprefix -I ,$(DIR_PATH))
main:main.o 
	$(CC) $(CLFLAGS) main.o -o main $(DLL_LIB)
main.o:main.c index.h
	$(CC) $(CCFLAGS) main.c $(DLL_LIB)

clean:
	rm -rf *.o 
