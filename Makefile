src = $(wildcard src/*.cpp)
obj = $(src:.cpp=.o)
CXXFLAGS = -Ofast -g -Wall
# linux:
LDFLAGS = -L/usr/X11R6/lib -lm -lpthread -lX11
# linux static:
# LDFLAGS = -L/usr/X11R6/lib -lm `pkg-config --libs --static x11` -lpthread -ldl -static
# Mac OS X
# LDFLAGS = -lm -lpthread -I/usr/X11R6/include -L/usr/X11R6/lib -lm -lpthread -lX11

all: install bin/gen

bin/gen: $(obj)
	$(CXX) -o $@ $^ $(LDFLAGS)

install:
	$(MAKE) -C 3rdparty

.PHONY: clean
clean:
	$(RM) $(obj) bin/gen

.PHONY: distclean
distclean: clean
	$(MAKE) -C 3rdparty clean
