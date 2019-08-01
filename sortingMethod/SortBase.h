#ifndef __SORT_BASE_H_
#define __SORT_BASE_H_
#include "util.h"
#include "DataObject.h"
#include <cstring>

using namespace std;

// SortBase
// this is a root class of another sorting class

template <typename T>
class SortBase
{
private:
  char name[100];
  string baw[3];
  DataObject<T> * arr;
public:
  SortBase(DataObject<T>& copy);
  void setName(const char * sortname);
  void setBAW(const string best, const string avg, const string worst);
  void showName() const;
  void showBAW() const;
  string& getBAW();
  DataObject<T>& getDataObject();
  virtual void showInfo() const = 0;
  virtual void sorting(){ };
  ~SortBase();
};

template <typename T>
SortBase<T>::SortBase(DataObject<T>& copy)
{
  arr = new DataObject<T>(copy);
  strcpy(name, "default name");
  setBAW("n","n","n");
  printstring("SortBase create");
}

template <typename T>
void SortBase<T>::setName(const char * sortname)
{
  int len = strlen(sortname);
  try
  {
    if (len > 100)
      throw 7;
    strcpy(name, sortname);
  }
  catch (int expn)
  {
    errexcept(expn);
  }
}

template <typename T>
void SortBase<T>::setBAW(const string best, const string avg, const string worst)
{
  baw[0] = best;
  baw[1] = avg;
  baw[2] = worst;
}

template <typename T>
void SortBase<T>::showBAW() const
{
  cout<<"Best : "<<baw[0]<<endl;
  cout<<"Avg  : "<<baw[1]<<endl;
  cout<<"Worst: "<<baw[2]<<endl;
}

template <typename T>
string& SortBase<T>::getBAW()
{
  return baw[1];
}

template <typename T>
void SortBase<T>::showName() const
{
  cout<<endl<<"------ ";
  cout<<"Method: "<<name<<" ------"<<endl;
  this -> showBAW();
}

template <typename T>
DataObject<T>& SortBase<T>::getDataObject()
{
  return *arr;
}

template <typename T>
SortBase<T>::~SortBase()
{
  printstring("SortBase delete");
}


#endif
