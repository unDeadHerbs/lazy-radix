#include <benchmark/benchmark.h>
#include <cstdio>
#include <random>
#include <vector>
#include <algorithm>

#include "lazy_radix.h"

std::random_device seed;
std::mt19937 gen(seed());

void lazy_radix_bench(benchmark::State& state) {
  state.PauseTiming();
  std::uniform_int_distribution<> rand(0, 1<<30);
  int* array = new int[state.range(0)];
  while (state.KeepRunning()) {
    for (int i = 0; i < state.range(0); i++)
      array[i] = rand(gen);
    state.ResumeTiming();
    //benchmark::DoNotOptimize(lazy_radix_big_space(array,state.range(0)));
    lazy_radix_big_space(array,state.range(0));
    benchmark::DoNotOptimize(array);
    state.PauseTiming();
  }
  delete[] array;
}

BENCHMARK(lazy_radix_bench)->RangeMultiplier(2)->Range(8, 2<<20);
//->Complexity(benchmark::oN);

void std_sort_bench(benchmark::State& state) {
  state.PauseTiming();
  std::uniform_int_distribution<> rand(0, 1<<30);
  int* array = new int[state.range(0)];
  while (state.KeepRunning()) {
    for (int i = 0; i < state.range(0); i++)
      array[i] = rand(gen);
    std::vector<int> v{array,array+state.range(0)};
    state.ResumeTiming();
    std::sort(v.begin(),v.end());
    state.PauseTiming();
    benchmark::DoNotOptimize(v);
  }
  delete[] array;
}

BENCHMARK(std_sort_bench)->RangeMultiplier(2)->Range(8, 2<<20);
BENCHMARK_MAIN();
