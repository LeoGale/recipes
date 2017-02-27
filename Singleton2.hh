#include <boost/noncopyable>
#include <assert.h>
#include <pthread.h>

namespace dabao {
    template<typename T>
    class Singleton : boost::noncopyable
    {
    public:
        Singleton() = delete;
        ~Singleton() = delete;
        
        static T& instance()
        {
            if(!value_)
            {
                value_ = new T();
                deleter_.set(value_);
            }
            return *value_;
        }
        static T* pointer()
        {
            return value_;
        }
        
    private:
        static void destructor(void* obj)
        {
            assert(obj == value_);
            typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
            T_must_be_complete_type dummy; (void)dummy;
            
            delete value_;
            value_ = nullptr;
        }
        
        class Deleter
        {
        public:
            Deleter()
            {
                pthread_create_key(&pkey_, &Singleton::destructor);
            }
            ~Deleter()
            {
                pthread_key_delete(pkey_);
            }
            void set(T* newObj)
            {
                assert(pthread_getspecific(pkey_) == nullptr);
                pthread_setspecific(pkey_, newObj);
            }
            pthread_key_t pkey_;
        };
        static T* value_;
        static Deleter deleter_;
    }
}

template <typename T>
__thread T* Singleton<T>::value_ = 0;

template <typename T>
typename Singleton<T>::Deleter Singleton<T>::deleter_ ;
