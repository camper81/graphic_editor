#pragma once
#include "change_types.h"

template<typename T>
struct Observer {
    virtual void handle(T& source,const CHANGE_TYPE& type) = 0;
};

template<typename T>
struct Observable {
    std::vector<Observer<T>*> observers;

    void addObserver(Observer<T>& observer) {
        observers.push_back(&observer);
    }

    void removeObserver(Observer<T>& observer) {
        observers.erase(std::remove(observers.begin(),observers.end(), observer), observers.end());
    }

    void notify(T& source, const CHANGE_TYPE& type) const{
        for(auto& observer: observers) {
            observer->handle(source, type);
        }
    }
};