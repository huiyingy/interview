#ifndef QIHOO_VECTOR_H_
#define QIHOO_VECTOR_H_
#include <cstdio>
#include <cassert>
namespace qh
{
    template<class T>
    class vector {
    public:
        //ctor
        vector()
            : data_(NULL), size_(0)
        {
        }

        explicit vector( size_t n, const T& value = T())
        {
            capa_ = n* FACTOR;
            if( capa_ < n+2){
                capa_ = n+2;
            }

            data_ = new T[capa_];
            for (size_t i = 0; i < n; i++)
            {
                data_[i] = value;
            }
            size_ = n;

        }

        vector<T>& operator=(const vector<T>& rhs)
        {
            if(data_ ){
                delete data_;
            }

            data_ = new T[rhs.capa_];
            size_ = rhs.size_;
            capa_ = rhs.capa_;
            for (size_t i = 0; i < size_; ++i)
            {
                data_[i] = rhs.data_[i];
            }

            return *this;
        }

        //dtor
        ~vector()
        {
            if (data_)
            {
                delete data_;
            }
        }

        //get
        size_t size() const
        {
            return size_;
        }


        T pop_back(){
            if(size_!=0 ){
                size_ --;
                return data_[size_];
            }
            else throw 0;
        }

        void resize (size_t n, const T& value = T());
        void clear(){size_ = 0;};
        bool empty() {return size_==0;}


        // set & get
        T& operator[](size_t index);

        // set
        void push_back(const T & element);
        void reserve(size_t n);
    private:
        T*      data_;
        size_t  size_;
        size_t  capa_;//数组容量
        const static double FACTOR;//数组生长因子

        void aux_extend(size_t  new_capa );//扩容辅助函数
    };

    template<class T>
    T& vector<T>::operator[](size_t index){
            if(index<size_ )
                return data_[index];
            else
                throw index;
        };

    template<class T>
    void vector<T>::push_back(const T & element){
            if(capa_ == size_ ){
                int tp = (capa_*FACTOR) > size_ + 2 ? (capa_*FACTOR): size_+2;
                aux_extend(tp);
            }

            data_[size_++] = element;
            return ;
        };

    template<class T>
    void vector<T>::aux_extend(size_t  new_capa ){
            T* tmp = data_;
            data_ = new T[new_capa];
            for (size_t i = 0; i < size_; ++i){
                data_[i] = tmp[i];
            }

            if (tmp){
                delete tmp;
            }
            
            capa_ = new_capa;
        };//扩容辅助函数

    template<class T>
    const double vector<T>::FACTOR = 1.5;       

    template<class T>
    void vector<T>::resize (size_t n, const T& value ){
/*      if(n<0 )
            return;*/

        if(n <=size_ ){
            size_ = n;
        }
        else{
            if(n>capa_ ){
                int tp = n;
                if( (capa_*FACTOR) > n)
                    tp = (capa_*FACTOR);
                 
                aux_extend(tp);
            }

            for (size_t i = size_; i < n; ++i){
                data_[i] = value;
            }
            size_ = n;
        }
        return;
    }


    template<class T>
    void vector<T>::reserve(size_t n){
        if(n<=capa_ )
            return;

        int tp = ((capa_*FACTOR) > n) ? (int)(capa_*FACTOR): n;
        aux_extend(tp);

    }

}

#endif


