///////////////////////////////////
// Author: Konstantin Lampalzer  //
// Date: 26.09.2018              //
// Project: PThreads             //
///////////////////////////////////

#include "customerCounter.h"
#include "customer.h"
#include "display.h"

#include <cstdlib>
#include <unistd.h>
#include <iostream>

CustomerCounter::CustomerCounter()
{
    counterNumber = 9999;
}

CustomerCounter::CustomerCounter(int _counterNumber, Display *_display)
{
    counterNumber = _counterNumber;
    display = _display;
}

CustomerCounter::~CustomerCounter()
{
}

void CustomerCounter::work()
{
    display->setFreeCustomerCounter(this);
}

void CustomerCounter::handleCustomer(Customer *customer)
{
    usleep(std::rand() % 1000000 + 1000000); // in the range 1000000-2000000
    std::cout << "Counter " << counterNumber << " done with customer " << customer->getTicketNumber() << std::endl;
    work();
}

const int CustomerCounter::getCounterNumber()
{
    return counterNumber;
}