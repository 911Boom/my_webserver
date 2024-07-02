//
// Created by 着魔之人 on 24-6-28.
//
#include<vector>



using namespace std;


class Observer{
public:
    virtual ~Observer(){}
    virtual void update()=0;
    //..
};

class Observable {
private:
    vector<Observer*> observers;

public:
    void register_(Observer* o);
    void unregister_(Observer* o);
    void notifi_() {
        for(auto o:observers) {
            o->update();
        }
    }
};


