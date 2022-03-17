TARGET = check-braces
PREFIX = /usr/local/bin

.PHONY: all clean install uninstall

all: $(TARGET)

$(TARGET): $(patsubst %.c, %.o, $(wildcard *.c))
	gcc $^ -lm -o $@

%.o: %.cpp
	gcc -c -MD $<

include $(wildcard *.d)

clean:
	-rm $(TARGET) *.o *.d

install:
	install ./$(TARGET) $(PREFIX)

uninstall:
	rm -rf $(PREFIX)/$(TARGET)
