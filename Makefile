.PHONY: all deps test clean

dep_includes=-I deps/simple_log/include -I deps/simple_flow/include -I ./deps/curl-7.54.0/include
dep_libs=deps/simple_flow/lib/libflowserver.a deps/simple_log/lib/libsimplelog.a ./deps/curl-7.54.0/lib/.libs/libcurl.a
deps_sos=-lrt

all: deps
	mkdir -p output/bin
	mkdir -p output/log
	g++ -g $(dep_includes) src/http_copy_main.cc src/curl_utils.cc src/monitor_handler.cc $(dep_libs) ${deps_sos} -o output/bin/http_copy
	cp -r conf output/

deps:
	# build for curl
	cd deps/curl-7.54.0 && ./configure && make

%.o: %.cc
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm -rf output/*
