#ifndef OBSERVER_H
#define OBSERVER_H

class Observer
{
public:
    virtual ~Observer() {}
    virtual void notify() const= 0;
    
};
#endif // OBSERVER_H