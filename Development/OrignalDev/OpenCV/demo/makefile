
CC = g++

CFLAGS = -Wall -O2

COMPILE = $(CC) $(CFLAGS) -c

OBJFILES := $(patsubst %.cc,%.o,$(wildcard *.cc))

INC=-I/opt/PDopencv/include/opencv
LIB=-lm -lcxcore -lcv -lcvaux -lhighgui
LIBS=-L/opt/PDopencv/lib

all: OpenCVdemo


OpenCVdemo: $(OBJFILES) 

	$(CC) $(LIBS) -o OpenCVdemo $(OBJFILES) $(LIB)


%.o: %.cc

	$(COMPILE) -o $@ $< $(INC)

clean:
	rm *.o