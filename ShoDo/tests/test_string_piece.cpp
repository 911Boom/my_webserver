//
// Created by 着魔之人 on 24-6-18.
//

#include "../base/StringPiece.h"
#include <iostream>

int main() {
  const char *a = "Hello,World";
  std::string b = "World,Hello";
  std::cout << a << ' ' << b << std::endl;
  StringPiece t(a);
  StringPiece t1(b);
  std::cout<<t.data()<<std::endl;
  std::cout<<t1.data()<<std::endl;
}