#include <vector>
#include <queue>
#include <array>

#include "lazy_radix.h"

#define END 32
// as there are only 0-31 bits
int one_after_pos(int position,int number){
	for(int i=position+1;i<END;i++)
		if(number & (1<<(32-i)))
		   return i;
  return END;
}

void lazy_radix_big_space(int array[], int const N){
  // Time(N,bits) = (bits/2+2)*N = O(N)
  // Space(N,bit) = (bits+2)*N   = O(N)
  std::queue<int> in;
  std::array<std::queue<int>,END> qs;
  std::queue<int> out;

  for(int i=0;i<N;i++)
    in.push(array[i]);

  while(in.size()){
      int elm=in.front();
      in.pop();
      int nex_pos=one_after_pos(-1,elm);
      if(nex_pos==END)
	out.push(elm);
      else
	qs[nex_pos].push(elm);
  }
	  
  
  for(int step=0;step<END;step++)
    while(qs[step].size()){
      int elm=qs[step].front();
      qs[step].pop();
      int nex_pos=one_after_pos(step,elm);
      if(nex_pos==END)
	out.push(elm);
      else
	qs[nex_pos].push(elm);
    }

  for(int i=0;i<N;i++)
    (array[i]=out.front()),out.pop();
}
