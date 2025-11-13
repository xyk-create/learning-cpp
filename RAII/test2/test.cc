#include <iostream>
#include <functional>
namespace my_ptr
{
    template<typename T>
    class shared_ptr
    {
    public:
        shared_ptr(T* obj,std::function<void(T*)> del=[](T* obj){delete obj;})
        :_obj(obj),_del(del)
        {
            _count = new int(1);
        }
        shared_ptr(shared_ptr<T>& ptr)
        {
            _count = ptr._count;
            _obj = ptr._obj;
            _del =  ptr._del;
            ++(_count);
        }
        shared_ptr<T>& operator=(shared_ptr<T>& ptr)
        {
            if(this == &ptr) return *this;
            if(--(*_count)==0)
            {
                _del(_obj);
                delete _count;
            }
            _count = ptr._count;
            _obj = ptr._obj;
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
        ~shared_ptr()
        {
            if(--(_count)==0)
            {
                _del(_obj);
                delete _count;
            }
        }
    private:
        int* _count;
        T* _obj;
        std::function<void(T*)> _del;
    };
}

class  test1
{
    public:
    test1(int a,std::string str)
    :_a(a),_str(str){}
    int _a;
    std::string _str;
};

int main()
{
    my_ptr::shared_ptr<test1> ptr(new test1(4,"7891"));
    my_ptr::shared_ptr<test1> ptr2(ptr);
    my_ptr::shared_ptr<test1> ptr3=ptr2;
    std::cout<<ptr3->_a<<std::endl;
    std::cout<<(*ptr3)._str<<std::endl;
    return 0;
}