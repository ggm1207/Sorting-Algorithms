#ifndef __SORT_HANDELR_H_
#define __SORT_HANDLER_H_
#include "./sortingMethod/SortBase.h"

using namespace std;

// adding text 
// adding sort
// worst, best, avg

class SortHandler
{
private:
  SortBase<long> * tl[20];
  SortBase<double> * td[20]; 
  int tl_len, td_len;
public:
  SortHandler();
  void addSortingMethod(SortBase<long> * st);
  void addSortingMethod(SortBase<double> * st);
  void allShowInfo() const;
  void allSorting();
  void nnSorting();
  void nlognSorting();
  ~SortHandler();
};

SortHandler::SortHandler() : tl_len(0), td_len(0)
{
  printstring("SortHandler Create");
}

void SortHandler::addSortingMethod(SortBase<long> * st)
{
  tl[tl_len++] = st;
}

void SortHandler::addSortingMethod(SortBase<double> * st)
{
  td[td_len++] = st;
}

void SortHandler::allShowInfo() const
{
  for(int i=0; i<tl_len; ++i)
    tl[i] -> showInfo();
  for(int i=0; i<td_len; ++i)
    td[i] -> showInfo();
}

void SortHandler::allSorting()
{
  for(int i=0; i<tl_len; ++i)
  {
    tl[i] -> showInfo();
    tl[i] -> sorting();
  }
  for(int i=0; i<td_len; ++i)
  {
    td[i] -> showInfo();
    td[i] -> sorting();
  }
}

void SortHandler::nnSorting()
{
  for(int i=0; i<tl_len; ++i)
  {
    string& baw = tl[i] -> getBAW();
    if (baw != "NlogN")
    {
      tl[i] -> showInfo();
      tl[i] -> sorting();
    }
  }
  for(int i=0; i<td_len; ++i)
  {
    string& baw = td[i] -> getBAW();
    if (baw != "NlogN")
    {
      td[i] -> showInfo();
      td[i] -> sorting();
    }
  }
}

void SortHandler::nlognSorting()
{
  for(int i=0; i<tl_len; ++i)
  {
    string& baw = tl[i] -> getBAW();
    if (baw == "NlogN")
    {
      tl[i] -> showInfo();
      tl[i] -> sorting();
    }
  }
  for(int i=0; i<td_len; ++i)
  {
    string& baw = td[i] -> getBAW();
    if (baw == "NlogN")
    {
      td[i] -> showInfo();
      td[i] -> sorting();
    }
  }
}

SortHandler::~SortHandler()
{
  for(int i=0; i<tl_len; ++i)
    delete tl[i];
  for(int i=0; i<td_len; ++i)
    delete td[i];
}
#endif