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

int right_of_pos(int position,int number){
	for(int i=position-1;i>=0;i--)
		if(number & (1<<i))
			return i;
	return -1;
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
		int nex_pos=right_of_pos(END,elm);
		if(nex_pos==-1)
			out.push(elm);
		else
			qs[nex_pos].push(elm);
	}
	  
	for(int step=0;step<END;step++)
		if(qs[step].size()){
			while(qs[step].size()){
				int elm=qs[step].front();
				qs[step].pop();
				int nex_pos=right_of_pos(step,elm);
				if(nex_pos==-1)
					out.push(elm);
				else
					qs[nex_pos].push(elm);
			}
			step=-1;
		}

	for(int i=0;i<N;i++)
		(array[i]=out.front()),out.pop();
}
