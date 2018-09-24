#include "display.h"

Display::Display()
{
    ticketNumber = 0;
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&condition, NULL);
}

Display::~Display()
{
}

void Display::setFreeCustomerCounter(int _customerCounter)
{
    customerCounter = _customerCounter;
    ticketNumber++;
    pthread_cond_broadcast(&condition);
}

int Display::getFreeCustomerCounter()
{
    return customerCounter;
}

int Display::getTicketNumber()
{
    return ticketNumber;
}

pthread_mutex_t Display::getLock()
{
    return lock;
}

pthread_cond_t Display::getCondition()
{
    return condition;
}