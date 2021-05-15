#pragma once

namespace KtSerial
{
template <class T>
class Singleton {
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static T& getInstance() {
        return create();
    }

private:
    static T& create() {
        static T t;
        return t;
    }

    static T& instance;
};

template <class T> T& Singleton<T>::instance = Singleton<T>::create();
} // namespace KtSerial
