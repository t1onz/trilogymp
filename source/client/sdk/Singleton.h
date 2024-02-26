// Singleton.h
#ifndef SINGLETON_H
#define SINGLETON_H

#include <cassert>

template <typename T>
class Singleton
{
protected:
    static T* m_pSingleton;

public:
    Singleton()
    {
        assert(!m_pSingleton && "A singleton instance already exists!");
        m_pSingleton = static_cast<T*>(this);
    }

    ~Singleton()
    {
        m_pSingleton = nullptr;
    }

    Singleton(const Singleton&) = delete; // Desabilita a c�pia
    Singleton& operator=(const Singleton&) = delete; // Desabilita a atribui��o

    static T& GetSingleton()
    {
        assert(m_pSingleton && "Singleton instance not created!");
        return *m_pSingleton;
    }

    static T* GetSingletonPtr()
    {
        return m_pSingleton;
    }
};

template <typename T>
T* Singleton<T>::m_pSingleton = nullptr; // Defini��o da inst�ncia est�tica

#endif // SINGLETON_H
