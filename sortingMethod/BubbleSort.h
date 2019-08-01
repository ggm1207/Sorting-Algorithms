#ifndef __BUBBLE_SORT_H_
#define __BUBBLE_SORT_H_
#include "util.h"
#include "SortBase.h"

using namespace std;

template <typename T>
class BubbleSort : public SortBase<T>
{
public:
  BubbleSort(DataObject<T>& copy);
  void showInfo() const;
  void sorting();
  ~BubbleSort();
};

template <typename T>
BubbleSort<T>::BubbleSort(DataObject<T>& copy) : SortBase<T>(copy)
{
  SortBase<T>::setName("Bubble Sort");
  SortBase<T>::setBAW("N^2","N^2","N^2");
  printstring("BubbleSort Create");
}

template <typename T>
void BubbleSort<T>::showInfo() const 
{
  SortBase<T>::showName();
}

template <typename T>
void BubbleSort<T>::sorting()
{
  printstring("BubbleSort start!");
  DataObject<T> &obj = SortBase<T>::getDataObject();
  T * * arr = obj.getData();
  int * numnum = obj.getnumnum();

  for(int f_index=0; f_index<obj.getcurnum(); ++f_index)
  {
    set_start();
    sorting_bubble(arr[f_index], 1, numnum[f_index]);
    set_end();
    call_setime(f_index);
  }
  // obj.head();
  // obj.end();
  obj.isSorting();
}

template <typename T>
BubbleSort<T>::~BubbleSort()
{
  printstring("Bubble Sort delete");
}
#endif