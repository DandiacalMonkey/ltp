#ifndef LTP_BASE_SINGLETON_H_
#define LTP_BASE_SINGLETON_H_

#include <QMutex>

namespace ltp
{
    namespace base
    {
        template <typename T>
        T& getInstance()
        {
            static QMutex mutex;
            static T* object = nullptr;
            if (object == nullptr)
            {
                QMutexLocker mutexLocker(&mutex);
                if (object == nullptr)
                {
                    object = new T();
                }
            }
            return *object;
        }
    }
}

#endif // LTP_BASE_SINGLETON_H_