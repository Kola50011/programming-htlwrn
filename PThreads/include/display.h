///////////////////////////////////
// Author: Konstantin Lampalzer  //
// Date: 26.09.2018              //
// Project: PThreads             //
///////////////////////////////////

#pragma once

#pragma once
#include <pthread.h>

class CustomerCounter;
class Display
{
private:
  CustomerCounter *customerCounter;
  int ticketNumber;

  void waitForCustomerResponse();

public:
  Display();
  ~Display();
  void setFreeCustomerCounter(CustomerCounter *counter);

  bool empty;

  // Need to be public as they dont't work , if I make getters
  pthread_cond_t counterFreeCondition;
  pthread_cond_t respondedCondition;
  pthread_mutex_t lock;

  // Getter + Setter
  CustomerCounter *getCustomerCounter();
  const int getTicketNumber();
};