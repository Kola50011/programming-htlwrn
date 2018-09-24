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