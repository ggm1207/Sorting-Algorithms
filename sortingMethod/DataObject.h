#ifndef __DATA_OBJECT_H_
#define __DATA_OBJECT_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "util.h"
using namespace std;

// DataObject have files that are not sorted.
template <typename T>
class DataObject
{
private:
  T * * arr;
  int fnum; // Addable number of files
  int * numnum;
  int curfilesnum; // current file number
public:
  DataObject(int filesnum);
  DataObject(const DataObject& copy);
  int getfnum() const;
  int* getnumnum() const;
  int getcurnum() const;
  void AddingTextFile(string filename, int datenum);
  void isSorting() const;
  void head() const;
  void end() const;
  T** getData(); // double pointer reference..?
  T& operator[](int idx){return arr[idx];}
  ~DataObject();
};

// template <typename T>
// int DataObject<T>::curfilesnum = 0;

template <typename T>
DataObject<T>::DataObject(int filesnum) : fnum(filesnum), curfilesnum(0)
{
  printstring("DataObject Create");
  try
  {
    if (filesnum <= 0)
      throw 1;
    arr = new T *[filesnum]; // heap array can't know a size
    numnum = new int[filesnum];
    if (arr == NULL)
      throw 2;
    if (numnum == NULL)
      throw 3;
  }
  catch(int expn)
  {
    errexcept(expn);
  }
}

template <typename T>
DataObject<T>::DataObject(const DataObject& copy)
{
  try
  {
    printstring("copy start!");
    arr = new T *[copy.fnum];
    if (arr == NULL)
      throw 8;
    fnum = copy.fnum;
    curfilesnum = copy.curfilesnum;
    numnum = copy.numnum;

    for(int i=0; i<curfilesnum; ++i)
    {
      arr[i] = new T[numnum[i]];
      if (arr[i] == NULL)
        throw 9;
    }
    for(int f_index=0; f_index<curfilesnum; ++f_index)
      for(int arr_index=0; arr_index<numnum[f_index]; ++arr_index)
        arr[f_index][arr_index] = copy.arr[f_index][arr_index];
    printstring("copy end!");
  }
  catch(int expn)
  {
    errexcept(expn);
  }
}

template <typename T>
int DataObject<T>::getfnum() const
{
  return fnum;
}

template <typename T>
int DataObject<T>::getcurnum() const
{
  return curfilesnum;
}

template <typename T>
int* DataObject<T>::getnumnum() const
{
  return numnum;
}

template <typename T>
void DataObject<T>::AddingTextFile(string filename, int datanum)
{
  try
  {
    if (curfilesnum >= fnum)
      throw 4;
    printstring("AddingTextFile");
    int cfs = curfilesnum;
    arr[cfs] = new T[datanum];
    numnum[cfs] = datanum;
    if (arr[cfs] == NULL)
      throw 5;

    ifstream openFile(filename.data());
    // 한 15초정도 오천만데이터
    if(openFile.is_open())
    {
      string line;
      int i = 0;
      while(getline(openFile, line))
      {
        stringstream ss(line);
        string str;
        while(ss>>str)
          arr[cfs][i++] = stol(str);
      }
      openFile.close();
    }
    else
      throw 6;
    curfilesnum++;
  }
  catch(int expn)
  {
    errexcept(expn);
  }
}

template <typename T>
void DataObject<T>::isSorting() const
{
  for(int i=0; i<curfilesnum; i++)
  {
    bool flag = true;
    for(int j=0; j<numnum[i] - 1; j++)
      if(arr[i][j] > arr[i][j+1])
      {
        flag = false;
        cout<<"file "<<i<<" is not sorted"<<endl;
        break;
      }
    if (flag)
      cout<<"file "<<i<<" is sorted"<<endl;
  }
}

template <typename T>
void DataObject<T>::head() const
{
  for(int i=0; i<curfilesnum; i++)
  {
    cout<<"file "<<i<<"'s"<<" head"<<endl;
    for(int j=0; j<10; j++)
      cout<<arr[i][j]<<" ";
    cout<<endl;
  }
}

template <typename T>
void DataObject<T>::end() const
{
  for(int i=0; i<curfilesnum; i++)
  {
    cout<<"file "<<i<<"'s"<<" end"<<endl;
    for(int j=numnum[i]-10; j<numnum[i]; j++)
      cout<<arr[i][j]<<" ";
    cout<<endl;
  }
}

template <typename T>
T * * DataObject<T>::getData()
{
  return arr;
}

template <typename T>
DataObject<T>::~DataObject()
{
  printstring("DataObject Delete");
  for(int i=0; i<curfilesnum; ++i)
    delete []arr[i];
  delete []arr;
}

#endif