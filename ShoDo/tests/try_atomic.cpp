//
// Created by 着魔之人 on 24-6-27.
//
#include <atomic>
#include <thread>
#include <mutex>
#include <ctime>
#include<vector>

using namespace std;

int tot = 0;
atomic<int> tot1 = 0;
mutex lock_;

void click1() {
    for (int i = 0; i < 100000; i++) {
        lock_.lock();
        tot += 5;
        lock_.unlock();
    }
}

void click2() {
    for (int i = 0; i < 100000; i++) tot1++;
}

void click3() {
    for (int i = 0; i < 100000; i++) tot++;
}


int main() {
    clock_t start = clock();
    vector<thread> threads(100);
    for (int i = 0; i < 100; i++) threads[i] = thread(click3);
    threads[0].
    for (auto &t: threads) t.join();
    clock_t end = clock();
    printf("result = %d, time = %lf\n", tot, (double) (end - start) / CLOCKS_PER_SEC);
    return 0;
}
