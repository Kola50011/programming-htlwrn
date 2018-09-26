#include "display.h"
#include "customer.h"
#include "customerCounter.h"
#include "numberGenerator.h"

#include <thread>
#include <iostream>
#include <unistd.h>

#define COUNTERS 5

void createCustomers(Display *display)
{
    std::cout << "Creating customers" << std::endl;
    NumberGenerator numberGenerator = NumberGenerator();
    while (true)
    {
        int customerNumber = numberGenerator.getNumber();
        std::cout << "\tCustomer " << customerNumber << " created " << std::endl;
        Customer *customer = new Customer(customerNumber, display);
        std::thread t(&Customer::waitForFreeCounter, customer);
        t.detach();
        usleep(1000000 * 1);
    }
}

void createCounters(Display *display)
{
    std::cout << "Creating counters" << std::endl;
    for (int i = 0; i < COUNTERS; i++)
    {
        CustomerCounter *counter = new CustomerCounter(i, display);
        std::thread t(&CustomerCounter::work, counter);
        t.detach();
    }
}

int main(int argc, char const *argv[])
{
    std::cout << "Started" << std::endl;

    Display *display = new Display();

    std::thread createCountersThread(&createCounters, display);
    std::thread createCustomersThread(&createCustomers, display);

    usleep(1000000 * 60); // Stop after 60 secs
    return 0;
}
