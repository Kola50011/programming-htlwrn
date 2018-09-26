#include "customer.h"
#include "customerCounter.h"
#include "display.h"

#include <pthread.h>
#include <iostream>

Customer::Customer(int _ticketNumber, Display *_display)
{
    ticketNumber = _ticketNumber;
    display = _display;
}

Customer::~Customer()
{
}

void Customer::respondToDisplay()
{
    display->empty = true;
    pthread_cond_broadcast(&display->respondedCondition);
}

void Customer::waitForFreeCounter()
{
    pthread_mutex_lock(&display->lock);

    waitForCorrectTicketNumber();
    respondToDisplay();

    CustomerCounter *counter = display->getCustomerCounter();

    pthread_mutex_unlock(&display->lock);

    counter->handleCustomer(this);
}

void Customer::waitForCorrectTicketNumber()
{
    while (display->getTicketNumber() != ticketNumber)
    {
        pthread_cond_wait(&display->counterFreeCondition, &display->lock);
    }
}

const int Customer::getTicketNumber()
{
    return ticketNumber;
}