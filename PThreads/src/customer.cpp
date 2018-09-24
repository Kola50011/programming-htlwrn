#include "display.h"
#include "customer.h"

#include <pthread.h>
#include <iostream>

Customer::Customer(int _ticketNumber, Display _display)
{
    ticketNumber = _ticketNumber;
    display = _display;
}

Customer::~Customer()
{
}

void *Customer::waitForFreeCounter(void *p)
{
    static_cast<Customer *>(p)->waitForFreeCounter();
}

void Customer::waitForFreeCounter()
{
    std::cout << "Waiting for ticket " << ticketNumber << std::endl;

    pthread_mutex_t lock = display.getLock();
    pthread_cond_t condition = display.getCondition();
    pthread_mutex_lock(&lock);
    while (display.getTicketNumber() != ticketNumber)
    {
        std::cout << "\tWrong ticket " << display.getTicketNumber() << std::endl;
        pthread_cond_wait(&condition, &lock);
    }
    std::cout << ticketNumber << " going to " << display.getFreeCustomerCounter() << std::endl;
    pthread_mutex_unlock(&lock);
}
