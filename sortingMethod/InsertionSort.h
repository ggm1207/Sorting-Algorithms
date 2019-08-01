#ifndef __INSERTION_SORT_H_
#define __INSERTION_SORT_H_
#include "util.h"
#include "SortBase.h"
using namespace std;

template <typename T>
class InsertionSort : public SortBase<T>
{
public:
  InsertionSort(DataObject<T>& copy);
  void showInfo() const;
  void sorting();
  ~InsertionSort();
};

template <typename T>
InsertionSort<T>::InsertionSort(DataObject<T>& copy) : SortBase<T>(copy)
{
  SortBase<T>::setName("Insertion Sort");
  SortBase<T>::setBAW("N","N^2","N^2");
  printstring("InsertionSort Create");
}

template <typename T>
void InsertionSort<T>::showInfo() const
{
  SortBase<T>::showName();
}

template <typename T>
void InsertionSort<T>::sorting()
{
  printstring("InsertionSort start!");
  DataObject<T> &obj = SortBase<T>::getDataObject();
  T * * arr = obj.getData();
  int * numnum = obj.getnumnum();

  for(int f_index=0; f_index<obj.getcurnum(); ++f_index)
  {
    set_start();
    sorting_insertion(arr[f_index], 1 , numnum[f_index]);
    
    set_end();
    call_setime(f_index);
  }
  // obj.head();
  // obj.end();
  obj.isSorting();
}

template <typename T>
InsertionSort<T>::~InsertionSort()
{
  printstring("Insertion Sort delete");
}

#endif