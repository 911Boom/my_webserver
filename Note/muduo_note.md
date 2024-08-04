C++可能出现的内存问题大致有这么几个方面:
1. 缓冲区溢出
2. 空悬指针/野指针
3. 重复释放
4. 内存泄露
5. 不配对的 new[]/delete
6. 内存碎片
使用智能指针可以解决前五个问题

shared_ptr本身的线程安全问题:
- 一个shared_ptr 可以在多个线程被同时读取
- 两个shared_ptr 对象实体可以被两个线程同时写入，“析构”算写操作
- 如果要从多个线程读写同一个shared_ptr，需要加锁



#### 2.4.2 Meyers'Singleton

```cpp
template <typename T>
class Singleton {
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    static T& getInstance() {
        static T instance;
        return instance;
    }
private:
    Singleton() = default;
    ~Singleton() = default;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;
};
```
该 Singleton 使用一个静态变量来储存数据，非常的简单明了，在 C++ 11 中，它是线程安全的。根据标准
§6.7 [stmt.dcl] p4：

If control enters the declaration concurrently while the variable is being initialized,

the concurrent execution shall wait for completion of the initialization.

C++ std::call_once 只运行一次并且线程安全

C++ thread 用法记录

```C++
#include <thread>

// #include<bits/stdc++.h>
#include<thread>
#include<string>
#include<iostream>
using namespace std;


void func(string a) {
    for(int i=0;i<10000;i++);
    // cout<<a<<endl;
    cout<<a<<' '<<this_thread::get_id()<<endl;
}

int main() {
    thread t(func,"Hello,World");
    cout<<"YES"<<endl;
    cout<<t.get_id();
    t.join();
    return 0;
}
```