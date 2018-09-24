#pragma once

#include <pthread.h>

class Display
{
private:
  int ticketNumber;
  int customerCounter;
  pthread_cond_t condition;
  pthread_mutex_t lock;

public:
  Display();
  ~Display();
  void setFreeCustomerCounter(int counter);
  int getFreeCustomerCounter();
  int getTicketNumber();
  pthread_mutex_t getLock();
  pthread_cond_t getCondition();
};