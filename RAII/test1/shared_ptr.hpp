#pragma once
#include <functional>
namespace my_ptr
{
    template <typename T>
    class shared_ptr
    {
    public:
        shared_ptr(std::function<void(T*)> del=[](T* obj){delete obj;})
            : _obj(nullptr),_del(del)
        {
            _count = new (0) size_t;
        }
        shared_ptr(T *obj,std::function<void(T*)> del=[](T* obj){delete obj;})
            : _obj(obj),_del(del)
        {
            _count = new size_t(1);
        }
        shared_ptr(const shared_ptr<T> &ptr)
        {
            _obj = ptr._obj;
            _count = ptr._count;
            (*_count)++;
        }
        shared_ptr<T> &operator=(const shared_ptr<T> &ptr)
        {
            if (this == &ptr)
                return *this;
            if (_obj != nullptr)
            {
                (*_count)--;
                if (*_count == 0)
                {
                    _del(_obj);
                    delete _count;
                }
            }
            _obj = ptr._obj;
            _count = ptr._count;
            _del = ptr._del;
            (*_count)++;
            return *this;
        }
        T& operator*()
        {
            return *_obj;
        }
        T* operator->()
        {
            return _obj;
        }
        T* get()
        {
            return _obj;
        }
        ~shared_ptr()
        {
            (*_count)--;
            if(*_count==0)
            {
                _del(_obj);
                delete _count;
            }
        }

    private:
        T *_obj;
        size_t *_count;
        std::function<void(T*)> _del;
    };
};
