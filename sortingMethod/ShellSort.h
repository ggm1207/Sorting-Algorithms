#ifndef __SHELL_SORT_H_
#define __SHELL_SORT_H_
#include "util.h"
#include "SortBase.h"

using namespace std;

template <typename T>
class ShellSort : public SortBase<T>
{
public:
  ShellSort(DataObject<T>& copy);
  void showInfo() const;
  void sorting();
  ~ShellSort();
};


template <typename T>
ShellSort<T>::ShellSort(DataObject<T> &copy) : SortBase<T>(copy)
{
  SortBase<T>::setName("Shell Sort");
  SortBase<T>::setBAW("N","N^1.5","N^2");
  printstring("ShellSort Create");
}

template <typename T>
void ShellSort<T>::showInfo() const
{
  SortBase<T>::showName();
}

template <typename T>
void ShellSort<T>::sorting()
{
  printstring("ShellSort start!");
  DataObject<T> &obj = SortBase<T>::getDataObject();
  T * * arr = obj.getData();
  int * numnum = obj.getnumnum();

  for(int f_index=0; f_index<obj.getcurnum(); ++f_index)
  {   
    int gaplist[4] = { 1024, 512, 64, 1};
    set_start();
    sorting_shell(arr[f_index], 1, numnum[f_index], gaplist);
    set_end();
    call_setime(f_index);
  }
  // obj.head();
  // obj.end();
  obj.isSorting();

}

template <typename T>
ShellSort<T>::~ShellSort()
{
  printstring("Shell Sort delete");
}

#endif