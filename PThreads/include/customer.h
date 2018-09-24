#pragma once

class Customer
{
private:
  int ticketNumber;
  Display display;

public:
  Customer(int _ticketNumber, Display _display);
  ~Customer();
  void waitForFreeCounter();
  static void *waitForFreeCounter(void *p);
};
