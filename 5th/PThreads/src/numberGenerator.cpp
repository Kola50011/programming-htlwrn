///////////////////////////////////
// Author: Konstantin Lampalzer  //
// Date: 26.09.2018              //
// Project: PThreads             //
///////////////////////////////////

#include "numberGenerator.h"

NumberGenerator::NumberGenerator()
{
  number = 0;
}

NumberGenerator::~NumberGenerator()
{
}

int NumberGenerator::getNumber()
{
  return ++number;
}