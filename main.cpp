#include <iostream>
#include "sortingHeader.h"
#include "SortHandler.h"
#include <algorithm>

int main(void)
{
  // I use template because of study.. 
  // but now i think overloading is a more better method than template.. 
  DataObject<long> test(4); // 숫자 확인 철저히
  test.AddingTextFile("./data/50K.txt", 50000);
  test.AddingTextFile("./data/500K.txt", 500000);
  test.AddingTextFile("./data/5M.txt", 5000000);
  // test.AddingTextFile("./data/50M.txt", 50000000);

  // long * * arr = test.getData();
  // set_start();
  // std::sort(arr[0], arr[0] + 5000000);
  // set_end();
  // call_setime(0);
  // long a = 3, b = 3;
  // SWAP(a,b);
  // cout<<a<<" "<<b<<endl;
  
  SortHandler * helper = new SortHandler();
  helper -> addSortingMethod(new InsertionSort<long>(test));
  helper -> addSortingMethod(new BubbleSort<long>(test));
  helper -> addSortingMethod(new SelectionSort<long>(test));
  helper -> addSortingMethod(new HeapSort<long>(test));
  helper -> addSortingMethod(new ShellSort<long>(test));
  helper -> addSortingMethod(new MergeSort<long>(test));
  helper -> addSortingMethod(new QuickSort<long>(test));
  
  // helper -> allShowInfo();
  // helper -> nnSorting();
  helper -> nlognSorting();
  delete helper;
  return 0;
}