#include "set.h"
#include <iostream>
using namespace std;
int main(){
  
  set<int> r1;
  r1.insert(72); //1
  r1.insert(3); //2
  r1.insert(9);   //3
  r1.insert(14);  //4 **
  r1.insert(93); //5
  r1.insert(108); //6(4)
  r1.insert(177); //7
  r1.insert(60); //8
  r1.insert(10); //9 **
  r1.insert(23); //10**
  r1.insert(65); //11 (1)
  r1.insert(30); //12
  r1.insert(40); //13
  r1.insert(49); //14
  r1.insert(51); //15
  r1.insert(98); //16
  r1.insert(894); //17 **
  r1.insert(300); //18**
  r1.insert(482); //19 **
  r1.insert(73); //20
  r1.insert(5); //21 (2)
  r1.insert(188); //22
  r1.insert(189); //23
  r1.insert(200); //24
  r1.insert(999); //25(3)
  r1.erase(894);
  r1.erase(482);
  r1.erase(14);
  // r1.erase(10);
  // r1.erase(72);
  // r1.erase(40);
  // r1.erase(300);
  // r1.erase(23);
  // r1.erase(65);
  // r1.erase(5);
  // r1.erase(999);
  // r1.erase(108);
  // r1.erase(98);
  // r1.erase(188);
  // r1.erase(93);
  r1.erase(189);
  r1.erase(49);
  r1.erase(200);
  r1.erase(177);
  r1.erase(73);
  r1.erase(60);
  r1.erase(51);
  r1.erase(30);
  r1.erase(3);
  r1.erase(9);

    r1.readArr();

  return 0;
}
