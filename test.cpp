#include <random>
#include <iostream>

#include "lazy_radix.h"

std::random_device seed;
std::mt19937 gen(seed());

#define SIZE 32
int main() {	
  std::uniform_int_distribution<> rand(0, 100);
  int* array = new int[SIZE];

  std::cout<<"Generating random numbers"<<std::endl;
  
  for (int i = 0; i < SIZE; i++){
	  array[i] = rand(gen);
	  std::cout<<array[i]<<" ";
  }
  std::cout<<std::endl;
  
  lazy_radix_big_space(array,SIZE);

  for (int i = 0; i < SIZE; i++)
	  std::cout<<array[i]<<" ";
  std::cout<<std::endl;
  delete[] array;
}
