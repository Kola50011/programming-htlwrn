#include "numberGenerator.h"
#include "display.h"
#include "customer.h"

#include <pthread.h>
#include <iostream>

#define CUSTOMERS 1
#define COUNTERS 1

int main(int argc, char const *argv[])
{
    std::cout << "Started" << std::endl;

    pthread_t customers[CUSTOMERS];

    NumberGenerator numberGenerator = NumberGenerator();
    Display display = Display();

    std::cout << "Creating customers" << std::endl;
    for (int i = 0; i < CUSTOMERS; i++)
    {
        int customerNumber = numberGenerator.getNumber();
        std::cout << "\tCustomer " << customerNumber << " created" << std::endl;
        Customer customer = Customer(customerNumber, display);
        pthread_create(&customers[i], NULL, Customer::waitForFreeCounter, &customer);
    }
    std::cout << "Customers created" << std::endl;

    display.setFreeCustomerCounter(1);
    display.setFreeCustomerCounter(2);

    for (int i = 0; i < CUSTOMERS; i++)
    {
        pthread_join(customers[i], NULL);
    }

    std::cout << "Done" << std::endl;
    return 0;
}
