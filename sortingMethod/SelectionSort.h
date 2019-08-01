#ifndef __SELECTION_SORT_H_
#define __SELECTION_SORT_H_
#include "util.h"
#include "SortBase.h"

using namespace std;

template <typename T>
class SelectionSort : public SortBase<T>
{
public:
  SelectionSort(DataObject<T>& copy);
  void showInfo() const;
  void sorting();
  ~SelectionSort();
};

template <typename T>
SelectionSort<T>::SelectionSort(DataObject<T> &copy) : SortBase<T>(copy)
{
  SortBase<T>::setName("Selection Sort");
  SortBase<T>::setBAW("N^2","N^2","N^2");
  printstring("SelectionSort Create");
}

template <typename T>
void SelectionSort<T>::showInfo() const
{
  SortBase<T>::showName();
}

template <typename T>
void SelectionSort<T>::sorting()
{
  printstring("SelectionSort start!");
  DataObject<T> &obj = SortBase<T>::getDataObject();
  T * * arr = obj.getData();
  int * numnum = obj.getnumnum();
  
  int m_idx=0;
  for(int f_index=0; f_index<obj.getcurnum(); ++f_index)
  {
    set_start();
    sorting_selection(arr[f_index], 1, numnum[f_index]);
    set_end();
    call_setime(f_index);
  }
  // obj.head();
  // obj.end();
  obj.isSorting();
}

template <typename T>
SelectionSort<T>::~SelectionSort()
{
  printstring("Selection Sort delete");
}

#endif