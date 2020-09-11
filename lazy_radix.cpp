#include <vector>
#include <queue>
#include <array>

int END=32; // as there are only 0-31 bits
int one_after_pos(int position,int number){
  return 0; // TODO
}

class Ring_Queue{
  std::vector<int> ring_queue;
  int head;
public:
  Ring_Queue(int size){
    ring_queue.reserve(size);
    for(int i=0;i<size;i++)
      ring_queue.push_back(i);
    // TODO: hint that vector never changes size again.
  }
};

void lazy_radix(int array[], int const N){
  auto min=[](int a,int b){if(a<b)return a;return b;};
  if(N<2)return;
  int indexs[N];
  int ring_queue[N];
  int min_index=END;
  for(int i=0;i<N;i++){
    int first_one=one_after_pos(-1,array[i]);
    indexs[i]=first_one;
    ring_queue[i]=i;
    min_index=min(min_index,first_one);
  }
  int head=-1;
  int old_head=head;
 goto_next:
  old_head=head;
  do{
    ++head%=N;
    if(head==old_head) min_index++;
    if(min_index==END) goto de_index;
  }while(ring_queue[head]==-1);
  goto move_elm_to_next;
  
 move_elm_to_next:
  if(indexs[ring_queue[head]]==min_index){
    int next_one=one_after_pos(indexs[ring_queue[head]],array[ring_queue[head]]);
    if(next_one==END){
      indexs[ring_queue[head]]=N-size_of(ring_queue);
      ring_queue[head]=-1;
    }else
      indexs[ring_queue[head]]=next_one;
  }else{
    goto goto_next;
  }
  goto goto_next;

 de_index:
  int done[N];
  for(int i=0;i<N;i++)
    done[indexs[i]]=array[i];
  for(int i=0;i<N;i++)
    array[i]=done[i];
  goto done;
  
 done:
  return;
}



void lazy_radix_big_space(int array[], int const N){
  // Time(N,bits) = (bits/2+2)*N = O(N)
  // Space(N,bit) = (bits+2)*N   = O(N)
  std::queue<int> in;
  std::array<std::queue<int>,8*sizeof(int)> qs;
  std::queue<int> out;

  for(int i=0;i<N;i++)
    in.push(array[i]);

  for(int step=0;step<int(8*sizeof(int));step++)
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
