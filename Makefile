benchmark:
	git clone https://github.com/google/benchmark.git
	cd benchmark
	cmake -E make_directory "build"
	cmake -E chdir "build" cmake -DCMAKE_BUILD_TYPE=Release ../
	cmake --build "build" --config Release

bench.bin: bench.cpp lazy_radix.cpp
	clang++ $^ -std=c++11 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o $@ -fsanitize=address -g

test.bin: test.cpp lazy_radix.cpp
	clang++ $^ -std=c++11 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o $@ -fsanitize=address -g
