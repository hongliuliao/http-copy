.PHONY: all test clean

dep_includes=-I deps/simple_log/include -I deps/hiredis/include -I deps/simple_flow/include
dep_libs=deps/simple_flow/lib/libflowserver.a deps/simple_log/lib/libsimplelog.a
dep_sos=-lcurl -lssl -lidn

all: 
	mkdir -p output/bin
	mkdir -p output/log
	g++ -g $(dep_includes) src/http_copy_main.cc src/curl_utils.cc src/monitor_handler.cc $(dep_libs) $(dep_sos) -o output/bin/http_copy
	cp -r conf output/

%.o: %.cc
	$(CXX) -c $(CXXFLAGS) $< -o $@
