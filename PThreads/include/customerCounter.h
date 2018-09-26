#pragma once

class Customer;
class Display;
class CustomerCounter
{
private:
  int counterNumber;
  Display *display;

public:
  CustomerCounter();
  CustomerCounter(int _counterNumber, Display *display);
  ~CustomerCounter();
  void handleCustomer(Customer *customer);
  void work();

  // Getter + Setter
  const int getCounterNumber();
};