#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

inline long getRandNum()
{
  return (((long)rand()<<15|rand()));
}

int main(int argc, char ** argv)
{
  unsigned int num = 50000000; 
  string filepath = "./50M.txt";

  cout << argc<<endl;
  if (argc > 1)
    num = atoi(argv[1]);
  if (argc > 2)
    filepath = argv[2];

  int columns = 100;
  int rows = num / columns;
  cout<<num<<endl;
  cout<<columns<<" "<<rows<<endl;
  srand((unsigned)time(NULL));

  ofstream writeFile(filepath.data());
  if(writeFile.is_open())
    for(int j=0; j<rows; j++)
    {
      for(int i=0; i<columns; i++)
      {
        writeFile<<getRandNum();
        writeFile<<" ";
      }
      writeFile<<"\n";
    }
    writeFile.close();
  return 0;
}