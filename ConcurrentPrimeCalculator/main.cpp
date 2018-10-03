#include <iostream>
#include <math.h>
#include <vector>
#include <thread>

using namespace std; 

void ParallellWorker(bool (*validPrims), int toCheck, int maxToCheck) {
    if (toCheck == 2) {
        for (int i = 2; toCheck * i <= maxToCheck; i++) {
            (*validPrims)[toCheck * i] = true;
        }
    } else {
        for (int i = 3; toCheck * i <= maxToCheck; i += 2) {
            (*validPrims)[toCheck * i] = true;
        }
    }
}

int Check(int maxToCheck) {
    bool p[maxToCheck + 1] = {false};
    bool (*validPrims)[maxToCheck + 1] = &p;

    int lastToRemove = sqrt(maxToCheck);
    cout << "LastToRemove: " << lastToRemove << endl;

    // Remove everything before lastToRemove Single-Threaded
    int currentPrim = 2;
    while (currentPrim <= lastToRemove) {
        for (int i = 2; currentPrim * i <= lastToRemove; i++) {
            (*validPrims)[currentPrim * i] = true;
        }

        // find next prim to remove
        currentPrim += 1;
        while ((*validPrims)[currentPrim] == true) {
            currentPrim += 1;
        }            
    }
    
    vector<int> primsBeforeLastToCheck;
    for (int i = 2; i < lastToRemove; i++) {
        if ((*validPrims)[i] == false) {
            primsBeforeLastToCheck.push_back(i);
        }
    }

    vector<thread> threads;
    // Now remove mutiples of 0 - lastToRemove
    for(auto const& toCheck: primsBeforeLastToCheck) {
        thread calcThread(&ParallellWorker, validPrims, toCheck, maxToCheck);
        calcThread.detach();
        threads.push_back(calcThread);
    }           

}

int main() {
    Check(1000);

    return 0;
}
