CXXFLAGS=-std=c++11 -stdlib=libc++

.PHONY: all
all: open

ray_trace: ray_trace.cpp *.hpp
	$(CXX) $(CXXFLAGS) ray_trace.cpp -o $@

.PHONY: render
render: ray_trace.ppm

ray_trace.ppm: ray_trace
	./ray_trace > ray_trace.ppm

.PHONY: clean
clean:
	rm -rf ray_trace.ppm ray_trace

.PHONY: open
open: render
	open -a ToyViewer ray_trace.ppm
