#include <iostream>
using std::cout;
using std::endl;
int main(int argc, char** argv)
{
   int index = 0;
   for (int i6 = 1; i6 <= 2; ++i6)
      for (int i5 = 1; i5 <= 3; ++i5)
        for (int i4 = 1; i4 <= 4; ++i4)
          for (int i3 = 1; i3 <= 5; ++i3)
            for (int i2 = 1; i2 <= 6; ++i2)
            {
              for (int i1 = 1; i1 <= 7; ++i1)
              {  
                cout << index++ << ' ';
              }
              cout << endl;
            }
   for (int i7 = 1; i7 <= 1; ++i7)
      for (int i6 = 1; i6 <= 2; ++i6)
        for (int i5 = 1; i5 <= 3; ++i5)
          for (int i4 = 1; i4 <= 4; ++i4)
            for (int i3 = 1; i3 <= 5; ++i3)
              for (int i2 = 1; i2 <= 6; ++i2)
              {
                for (int i1 = 1; i1 <= 7; ++i1)
                {  
                  cout << index++ << ' ';
                }
                cout << endl;
              }
}
