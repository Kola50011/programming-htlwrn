///////////////////////////////////
// Author: Konstantin Lampalzer  //
// Date: 26.09.2018              //
// Project: PThreads             //
///////////////////////////////////

#pragma once
class NumberGenerator
{
private:
  int number;

public:
  NumberGenerator();
  ~NumberGenerator();

  // Getter + Setter
  int getNumber();
};