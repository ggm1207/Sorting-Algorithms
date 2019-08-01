#ifndef __MERGE_SORT_H_
#define __MERGE_SORT_H_
#include "util.h"
#include "SortBase.h"
using namespace std;

template <typename T>
class MergeSort : public SortBase<T>
{
public:
  MergeSort(DataObject<T>& copy);
  void showInfo() const;
  void sorting();
  ~MergeSort();
};


template <typename T>
MergeSort<T>::MergeSort(DataObject<T>& copy) : SortBase<T>(copy)
{
  SortBase<T>::setName("Merge Sort");
  SortBase<T>::setBAW("NlogN","NlogN","NlogN");
  printstring("MergeSort Create");
}

template <typename T>
void MergeSort<T>::showInfo() const
{
  SortBase<T>::showName();
}

template <typename T>
void MergeSort<T>::sorting()
{
  printstring("MergeSort start!");
  DataObject<T> &obj = SortBase<T>::getDataObject();
  T * * arr = obj.getData();
  int * numnum = obj.getnumnum();

  for(int f_index=0; f_index<obj.getcurnum(); ++f_index)
  {
    set_start();
    sorting_merge(arr[f_index], 1, numnum[f_index]);
    set_end();
    call_setime(f_index);
  }
  // obj.head();
  // obj.end();
  obj.isSorting();
}

template <typename T>
MergeSort<T>::~MergeSort()
{
  printstring("Merge Sort delete");
}

#endif