TARGET = logParse

all: $(TARGET)

logParse: logParse.o
	gcc -o$@ $^

%.o: %.c
	gcc -c -o$@ $<

clean:
	rm -f *.o $(TARGET)
