SRCS = $(wildcard src/*.c src/*/*.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))
#CFLAGS += -Isrc -fPIC
CFLAGS += -Isrc
LDFLAGS += -fPIC -ldl -shared
LIBNAME = libcave.so

all: $(LIBNAME)

$(LIBNAME): $(OBJS)
	$(LINK.cc) -shared $^ $(LDLIBS) -o $@

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $^


clean:
	rm -f $(LIBNAME) $(OBJS)
