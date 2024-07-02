//
// Created by 着魔之人 on 24-6-28.
//
#include <memory>
#include <vector>
#include <list>
#include <mutex>
class Observer{
public:
    virtual ~Observer(){}
    virtual void update()=0;
    //..
};


class Observable {
public:
    void add_(std::weak_ptr<Observer> o);
    void notify();

private:
    std::list<std::weak_ptr<Observer>> observers_;
    mutable std::mutex m_;

};

void Observable::notify() {
    m_.lock();
    for(auto o= observers_.begin(); o!=observers_.end();) {
        if(auto p = o->lock()) {
            p->update();
            ++o;
        }
        else o = observers_.erase(o);
    }
    m_.unlock();
}

