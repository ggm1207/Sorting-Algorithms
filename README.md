Sorting-Algorithms
============
## 구건모 개인 프로젝트
*****

### 1. 개요

```
  c++ 공부 후 배웠던 문법을 사용해서 어떤 프로젝트를 해야지 재밌게 할 수 있을까 고민하다가 
  평소에 관심 있었던 정렬 알고리즘을 직접 짜기로 했다. 다양한 정렬 알고리즘과 c++ 문법에 익숙해지고 
  더 나아가 새로운 정렬 알고리즘을 구현하는 것을 최종목표로 한다.
```

<br><br>

### 2. 목표
  * 가독성이 높은 코드
  * 재사용성이 쉬운 코드
  * template, virtual, inline, class ... 등 다양한 문법 사용하기
  * 코드 리팩토링을 통하여 코드 최적화 하기
  * 새로운 정렬 알고리즘
  
<br>

### 3. 기본 클래스

<br>
<dl>
<dt>DataObject : 데이터를 처리하는 클래스입니다.</dt>
<dd> 
다양한 파일을 읽어서 데이터를 처리할 수 있도록 한다. 
<br>현재는 txt 파일을 읽는 method 밖에 없지만 만약 csv 파일을 읽기 원한다면 AddingCsvFile 메소드를 추가 작성할 수 있다. <br>
여러개의 파일을 저장할 수 있다.
</dd>
</dl> 

<br>

```cpp
template typename <T>
class DataObject
{
private:
  T * * arr;
  int fnum; // Addable number of files
  int * numnum;
  int curfilesnum; // current file number
public:
  DataObject(int filesnum); // 
  DataObject(const DataObject& copy);
  int getfnum() const;
  int* getnumnum() const;
  int getcurnum() const;
  void AddingTextFile(string filename, int datenum);
  void isSorting() const;
  void head() const; // show data's haed
  void end() const; // show data's end
  T** getData(); // double pointer reference..?
  T& operator[](int idx){return arr[idx];}
  ~DataObject();
};
```

<br>
<dl>
<dt>SortBase : Sorting 함수의 부모클래스입니다. </dt>
<dd>
모든 정렬알고리즘들은 SortBase를 상속 받아서 작성해야 된다. -> SortHandler 에서 관리를 해야하기 때문에..
</dd>
</dl> 

<br>

```cpp
template typename <T>
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
```

<br>
<dl>
<dt>SortHandler : Sorting 함수들을 관리합니다. </dt>
<dd>
정렬 알고리즘 클래스들은 생성된후 SortHandler에 추가 가능하며 SortHandler는 그들을 관리한다.
</dd>
</dl>

<br>

```cpp
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
```

<br>

### 4. 기본 클래스 활용 방법

<br>

**예시 클래스**

```cpp
template typename <T>
class InsertionSort : public SortBase <T>
{
public:
  InsertionSort(DataObject<T>& copy);
  void showInfo() const;
  void sorting();
  ~InsertionSort();
};
```

<br>

**InsertionSort(DatObject<T>& copy)**

> 생성자는 DataObject를 받는다. 이름을 입력한 후 시간 복잡도를 Best, Avg, Worst 순으로 입력한다.

```cpp
template <typename T>
InsertionSort<T>::InsertionSort(DataObject<T>& copy) : SortBase<T>(copy)
{
  SortBase<T>::setName("Insertion Sort");
  SortBase<T>::setBAW("N","N^2","N^2");
  printstring("InsertionSort Create");
}
```

<br>

**void showInfo const()**
> 생성자에서 입력한 Sorting Method 의 정보를 보여준다.

```cpp
template <typename T>
void InsertionSort<T>::showInfo() const
{
  SortBase<T>::showName();
}
```
<br>
<b>void sorting()</b>

> 1. getDataObject()를 사용하여 obj가 정렬해야할 데이터를 참조한다.<br>
> 2. getDataObject 에 등록된 모든 파일들을 정렬할 수 있게 반복문을 구성한다.<br>
> 3. set_start() 를 호출하여 시간 체크를 시작한다.<br>
> 4. 'sortingMethod/utils.h' 에 정의된 sorting_insertion() 함수를 실행하여 정렬을 실행한다.
> void sorting_insertion(T * ar, int start, int end, int gap = 1)
> 배열의 주소값과, 시작 인덱스, 끝 인덱스를 입력값으로 받는다. gap 은 쉘 정렬을 위해 사용된다.
> 사용자는 utils.h 에 정의된 여러 정렬 함수를 조합하여 새로운 정렬 함수를 만들 수 있다. <br>
> 5. set_end() 을 호출하여 시간체크를 멈춘다.
> 6. call_setime(f_index)를 호출하여 T[f_index] 를 정렬하는데 걸린 시간을 출력한다.
> 7. obj.isSorting()를 호출하여 데이터가 잘 정렬되어 있는지 확인합니다.

```cpp
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
```

### 5. 실행 결과

**main.cpp**

```cpp
int main(void)
{
  DataObject<long> test(4); // 숫자 확인 철저히
  test.AddingTextFile("./data/50K.txt", 50000);
  test.AddingTextFile("./data/500K.txt", 500000);

  SortHandler * helper = new SortHandler();
  helper -> addSortingMethod(new InsertionSort<long>(test));
  helper -> addSortingMethod(new BubbleSort<long>(test));
  helper -> addSortingMethod(new SelectionSort<long>(test));
  helper -> addSortingMethod(new HeapSort<long>(test));
  helper -> addSortingMethod(new ShellSort<long>(test));
  helper -> addSortingMethod(new MergeSort<long>(test));
  helper -> addSortingMethod(new QuickSort<long>(test));
  
  // helper -> allShowInfo();
  // helper -> nnSorting();
  helper -> nlognSorting();
  delete helper;
  return 0;
}
```

<pre>
------ Method: Heap Sort ------
Best : NlogN
Avg  : NlogN
Worst: NlogN
file 0: Time to sort: 0.016958 s
file 1: Time to sort: 0.232408 s
file 0 is sorted
file 1 is sorted

------ Method: Merge Sort ------
Best : NlogN
Avg  : NlogN
Worst: NlogN
file 0: Time to sort: 0.010007 s
file 1: Time to sort: 0.147607 s
file 0 is sorted
file 1 is sorted

------ Method: Quick Sort ------
Best : NlogN
Avg  : NlogN
Worst: N^2
file 0: Time to sort: 0.012964 s
file 1: Time to sort: 0.141609 s
file 0 is sorted
file 1 is sorted
</pre>

### 5. 끝 마치며
  - makeUnsortedFile.cpp 를 활용해서 비정렬된 파일을 만들 수 있습니다.
  - Visual code 에서 .vscode/tasks.json 파일을 사용하여 쉽게 빌드할 수 있습니다. (ctrl + shift + p) -> sorting 빌드 선택
  아직 프로젝트는 현재 진행형입니다.
