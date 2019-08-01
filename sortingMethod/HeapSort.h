#ifndef __HEAP_SORT_H_
#define __HEAP_SORT_H_
#include "util.h"
#include "SortBase.h"

using namespace std;

template <typename T>
class HeapSort : public SortBase<T>
{
public:
  HeapSort(DataObject<T>& copy);
  void showInfo() const;
  void sorting();
  ~HeapSort();
};

template <typename T>
HeapSort<T>::HeapSort(DataObject<T>& copy) : SortBase<T>(copy)
{
  SortBase<T>::setName("Heap Sort");
  SortBase<T>::setBAW("NlogN","NlogN","NlogN");
  printstring("HeapSort Create");
}


template <typename T>
void HeapSort<T>::showInfo() const
{
  SortBase<T>::showName();
}

template <typename T>
void HeapSort<T>::sorting()
{
  printstring("HeapSort start!");
  DataObject<T> &obj = SortBase<T>::getDataObject();
  T * * arr = obj.getData();
  int * numnum = obj.getnumnum();

  for(int f_index=0; f_index<obj.getcurnum(); ++f_index)
  {
    set_start();
    make_heap(arr[f_index], 1, numnum[f_index]);
    sorting_heap(arr[f_index], 1, numnum[f_index]);
    set_end();
    call_setime(f_index);
  }
  // obj.head();
  // obj.end();
  obj.isSorting();
}

template <typename T>
HeapSort<T>::~HeapSort()
{
  printstring("Heap Sort delete");
}
#endif