benchmark:
	git clone https://github.com/google/benchmark.git
	cd benchmark
	cmake -E make_directory "build"
	cmake -E chdir "build" cmake -DCMAKE_BUILD_TYPE=Release ../
	cmake --build "build" --config Release

%.bin: %.cpp benchmark
	clang++ $< -std=c++11 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o $@