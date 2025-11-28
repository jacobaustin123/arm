CC = clang
AS = clang

CFLAGS = -O2 -Wall
ASFLAGS = -c

TARGET = simd_test
OBJECTS = main.o simd_add.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<

simd_add.o: simd_add.s
	$(AS) $(ASFLAGS) -o $@ $<

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all clean
