#include <benchmark/benchmark.h>
#include <cstdio>
#include <random>

#include "lazy_radix.h"

std::random_device seed;
std::mt19937 gen(seed());

void lrbs_benchmark(benchmark::State& state) {
  state.PauseTiming();
  std::uniform_int_distribution<> rand(0, 100);
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

BENCHMARK(lrbs_benchmark)->RangeMultiplier(2)->Range(8, 8<<10)->Complexity(benchmark::oN);
BENCHMARK_MAIN();
