CXXFLAGS = -g -pedantic -Wall -Wextra -I./ -std=c++17
LDFLAGS = -g

SRCS_CPP = main.cpp
OBJS = $(SRCS_CPP:.cpp=.o)

.PHONY: all
all: a.out

a.out: $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS)

$(OBJS): Point.hpp Ray.hpp Vector.hpp Sphere.hpp PGMOut.hpp Raytracer.hpp

.PHONY: clean
clean:
	rm -f *.o a.out