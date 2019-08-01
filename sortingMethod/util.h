#ifndef __UTIL_H_
#define __UTIL_H_
#include <iostream>
#include <sys/time.h>

#define ISMAX(a,b) (((a)>(b)) ? true : false)
#define ISMIN(a,b) (((a)<(b)) ? true : false)
#define MAX(a,b) (((a)>(b)) ? a : b)
#define MIN(a,b) (((a)<(b)) ? a : b)

using namespace std;

struct timeval ggm_start, ggm_end;
double diff;
int cur, child, cnt, s, e, i, j, k, lefts, rights;
long lc, rc, pivot;
bool flag;
long c_arr[50000000];

// printstring used for debugging.
template <typename T>
void printstring(const T& str)
{
  // cout<<str<<endl;
}

void errexcept(int expn)
{
  cout<<"Error code: "<<expn<<endl;
}

void set_start()
{
  gettimeofday(&ggm_start, NULL);
}

void call_setime(int f_index)
{
  cout<<"file "<<f_index<<": ";
  diff = ((double)ggm_end.tv_sec - (double)ggm_start.tv_sec) + ((double)((double)ggm_end.tv_usec - (double)ggm_start.tv_usec) / 1000000);
  // %ld == long
  printf("Time to sort: %f s\n",diff);
}

void set_end()
{
  gettimeofday(&ggm_end, NULL);
}

template <typename T>
inline void SWAP(T& x,T& y) 
{
  if (x != y){ // if x == y then put 0
    x = x ^ y;
    y = x ^ y;
    x = x ^ y;
  }
}

template <typename T>
void sorting_bubble(T * ar, int start, int end) // 0 , 5000 (0 ~ 4999)
{
  for(int i=start-1; i<end; ++i)
    for(int j=start-1; j<end-i-1; ++j)
      if ( ISMAX(ar[j], ar[j+1]))
        SWAP(ar[j],ar[j+1]);
}

template <typename T>
void sorting_insertion(T * ar, int start, int end, int gap = 1)
{
  int temp, j;
  for(int i=start-1; i<end; i += gap)
  {
    temp = ar[i]; // value to insert
    for(j=start-1; j<i; j += gap) // find insertion location
      if(!ISMAX(temp, ar[j]))
        break;
    
    for(int k=i; k>j; k -= gap) // array push back
      ar[k] = ar[k-gap];

     ar[j] = temp; // insertion
  }
}

template <typename T>
void make_heap(T * ar, int start, int end)
{
  for(int i=start; i<end; ++i)
  {
    cur = i + 1;
    while(cur > 1)
    {
      if(ar[int(cur/2)-1] < ar[cur-1])
      {
        SWAP(ar[int(cur/2)-1], ar[cur-1]);
        cur = int(cur/2);
      }
      else
        break;
    }
  }
}

template <typename T>
void sorting_heap(T * ar, int start, int end)
{
  for(int i=end-1; i>start-1; --i) // 4999 ~ 0
  {
    cur = 1; child = 2;
    SWAP(ar[i],ar[0]); // reject max to i
    while(child <= i)
    {
      lc = 0; rc = 0;
      if (child + 1 <= i)
        rc = ar[child];
      if (child <= i)
        lc = ar[child - 1];
      if (ISMAX(lc , rc)) // lc bigger 
        if (ISMAX(lc, ar[cur-1]))
        {
          SWAP(ar[child-1], ar[cur-1]);
          cur = child;
          child = cur * 2;
        }
        else
          break;
      else
        if (ISMAX(rc, ar[cur-1]))
        {
          SWAP(ar[child], ar[cur-1]);
          cur = child + 1;
          child = cur * 2;
        }
        else
          break;
    }
  }
}

template <typename T>
void sorting_selection(T * ar, int start, int end)
{
  int m_idx;
  for(int i=start-1; i<end; ++i) // put num this position
  {
    m_idx = i;
    for(int j=i+1; j<end; ++j)
      if (ISMIN(ar[j],ar[m_idx]))
        m_idx = j;
    if (i != m_idx)
      SWAP(ar[i], ar[m_idx]);
  }
}


template <typename T>
void sorting_shell(T * ar, int start, int end, int * gap_list)
{
  for(int gapnum=0; gapnum<4; ++gapnum) // 100
    for(int i=0; i<gap_list[gapnum]; ++i)
      sorting_insertion(ar, start+i, end, gap_list[gapnum]);
}

template <typename T>
void merge(T *ar, int start, int end, int mid)
{
  lefts = start - 1;
  rights = mid;
  cnt = 0;
  while(lefts <= mid-1 && rights <= end-1 )
  {
    if (ar[lefts] <= ar[rights])
      c_arr[cnt++] = ar[lefts++];
    else
      c_arr[cnt++] = ar[rights++];
  }

  if (lefts > mid - 1)
  {
    while(rights != (end))
      c_arr[cnt++] = ar[rights++];
  }
  else
  {
    while(lefts != (mid))
      c_arr[cnt++] = ar[lefts++];
  }

  for (i=0; i<cnt; ++i)
    ar[start-1+i] = c_arr[i];
}

template <typename T>
void sorting_merge(T * ar, int start, int end)
{
  if (start < end)
  {
    int mids = (start+end)/2;
    sorting_merge(ar, start, mids);
    sorting_merge(ar, mids+1, end);
    merge(ar, start, end, mids);
  }
}

template <typename T>
int quick(T * ar, int start, int end)
{
  pivot = ar[start-1];
  lefts = start; rights = end-1;
  do
  {
    while(ar[lefts] < pivot && lefts < end)
      lefts++;
    while(ar[rights] > pivot && rights > start-1)
      rights--;
    if(lefts < rights)
      SWAP(ar[lefts], ar[rights]);
  } while(lefts < rights);
  SWAP(ar[start-1], ar[rights]);
  return rights + 1;
}

template <typename T>
void sorting_quick(T * ar, int start, int end)
{
  if (start < end)
  {
    int pp = quick(ar, start, end);
    sorting_quick(ar, start, pp-1);
    sorting_quick(ar, pp+1, end);
  }
}
#endif