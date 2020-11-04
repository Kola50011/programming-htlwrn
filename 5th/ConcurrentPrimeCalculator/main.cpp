#include <iostream>
#include <math.h>
#include <vector>
#include <thread>
#include <mutex>

using namespace std; 

std::mutex mylock;
vector<bool> validPrims;

void ParallellWorker(vector<bool> &validPrims, int toCheck, int maxToCheck) {
    if (toCheck == 2) {
        for (int i = 2; toCheck * i <= maxToCheck; i++) {
            mylock.lock();
            validPrims[toCheck * i] = true;
            mylock.unlock();
        }
    } else {
        for (int i = 3; toCheck * i <= maxToCheck; i += 2) {
            mylock.lock();
            validPrims[toCheck * i] = true;
            mylock.unlock();
        }
    }


}

int Check(int maxToCheck) {
    static const int size = maxToCheck + 1;

    validPrims.assign(size, false);
    // bool validPrims[maxToCheck + 1] = &p;

    int lastToRemove = sqrt(maxToCheck);
    cout << "LastToRemove: " << lastToRemove << endl;

    // Remove everything before lastToRemove Single-Threaded
    int currentPrim = 2;
    while (currentPrim <= lastToRemove) {
        for (int i = 2; currentPrim * i <= lastToRemove; i++)
            validPrims[currentPrim * i] = true;

        // find next prim to remove
        currentPrim += 1;
        while (validPrims[currentPrim] == true)
            currentPrim += 1;      
    }
    
    vector<int> primsBeforeLastToCheck;
    for (int i = 2; i < lastToRemove; i++)
        if (validPrims[i] == false)
            primsBeforeLastToCheck.push_back(i);

    vector<thread> threads;
    // Now remove mutiples of 0 - lastToRemove
    for (auto &toCheck: primsBeforeLastToCheck) {
        std::thread t(ParallellWorker, std::ref(validPrims), toCheck, maxToCheck);
        threads.push_back(move(t));
    }

    for (auto &t: threads)
        t.join();

    int amount = 0;
    for (int i = 2; i < maxToCheck; i++) {
        if (validPrims[i] == false) {
            cout << i << endl;
            amount++;
        }
    }
    cout << "Amount: " << amount << endl;  
}

int main() {
    Check(1000);

    return 0;
}
