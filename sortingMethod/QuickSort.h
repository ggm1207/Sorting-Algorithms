#ifndef __QUICK_SORT_H_
#define __QUICK_SORT_H_
#include "util.h"
#include "SortBase.h"

using namespace std;

template <typename T>
class QuickSort: public SortBase<T>
{
public:
  QuickSort(DataObject<T>& copy);
  void showInfo() const;
  void sorting();
  ~QuickSort();
};

template <typename T>
QuickSort<T>::QuickSort(DataObject<T>& copy) : SortBase<T>(copy)
{
  SortBase<T>::setName("Quick Sort");
  SortBase<T>::setBAW("NlogN","NlogN","N^2");
  printstring("QuickSort Create");
}


template <typename T>
void QuickSort<T>::showInfo() const
{
  SortBase<T>::showName();
}

template <typename T>
void QuickSort<T>::sorting()
{
  printstring("QuickSort start!");
  DataObject<T> &obj = SortBase<T>::getDataObject();
  T * * arr = obj.getData();
  int * numnum = obj.getnumnum();

  for(int f_index=0; f_index<obj.getcurnum(); ++f_index)
  {
    set_start();
    sorting_quick(arr[f_index], 1, numnum[f_index]);
    set_end();
    call_setime(f_index);
  }
  // obj.head();
  // obj.end();
  obj.isSorting();
}

template <typename T>
QuickSort<T>::~QuickSort()
{
  printstring("Quick Sort delete");
}
#endif