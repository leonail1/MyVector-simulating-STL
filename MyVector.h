//
//  MyVector.h
//  MyVector
//
//  Created by 林正刚 on 2022/11/18.
//

#ifndef MyVector_h
#define MyVector_h
#include<iostream>
#include<algorithm>
#include<assert.h>



template<class _Tp>
class MyVector{
    typedef const _Tp* const_pointer;
    typedef _Tp* pointer;
    typedef _Tp& reference;
    typedef const _Tp& const_reference;
    typedef size_t size_type;
    typedef _Tp value_type;
private:
    class ReverseIterator{//反向迭代器
    public:
        //friend class MyVector;
        ReverseIterator(pointer p=nullptr):ptr(p){}//构造函数，默认参数为nullptr
        reference operator*()const{return *ptr;}//返回pointer指向的值
        pointer operator->()const{return ptr;}//返回pointer本身
        pointer operator++(){
            return --ptr;
        }//前置++,由于是反向迭代器，返回ptr--
        const pointer operator++(int){
            pointer tmp=ptr;//存储自增前的对象
            --(*this);//对“这个”对象应用已定义的前置++操作
            return tmp;//返回修改前的对象
        }
        pointer operator--(){return ++ptr;}//反向迭代，--等于++
        const pointer operator--(int){//后置++，返回const使得i++++不合法
            pointer tmp=ptr;//存储自增前的对象
            ++(*this);//对“这个”对象应用已定义的前置++操作
            return tmp;//返回修改前的对象
        }
        bool operator==(ReverseIterator pointer){return this->ptr==pointer.ptr;}
        bool operator==(pointer pointer){return this->ptr==pointer;}
        bool operator!=(ReverseIterator pointer){return this->ptr!=pointer.ptr;}
        bool operator!=(pointer pointer){return this->ptr!=pointer;}
        bool operator<(ReverseIterator pointer){return this->ptr>pointer.ptr;}
        bool operator<(pointer pointer){return this->ptr>pointer;}
        bool operator>(ReverseIterator pointer){return this->ptr<pointer.ptr;}
        bool operator>(pointer pointer){return this->ptr<pointer;}
        bool operator<=(ReverseIterator pointer){return this->ptr>=pointer.ptr;}
        bool operator<=(pointer pointer){return this->ptr>=pointer;}
        bool operator>=(ReverseIterator pointer){return this->ptr<=pointer.ptr;}
        bool operator>=(pointer pointer){return this->ptr<=pointer;}
        ReverseIterator operator+(size_type _size){//只能作为左值
            for(auto i=0;i<_size;i++){
                ++(*this);
            }
            return this->ptr;
        }
        ReverseIterator operator-(size_type _size){
            for(auto i=0;i<_size;i++){
                --(*this);
            }
            return this->ptr;
        }
        ReverseIterator& operator=(pointer ptr){
            this->ptr=ptr;//指针赋值
            return ptr;
        }
    private:
        pointer ptr;
    };
    class ConstReverseIterator{//反向迭代器
    public:
        //friend class MyVector;
        ConstReverseIterator(pointer p=nullptr):ptr(p){}//构造函数，默认参数为nullptr
        reference operator*()const{return *ptr;}//返回pointer指向的值
        pointer operator->()const{return ptr;}//返回pointer本身
        bool operator==(ReverseIterator pointer){return this->ptr==pointer.ptr;}
        bool operator==(pointer pointer){return this->ptr==pointer;}
        bool operator!=(ReverseIterator pointer){return this->ptr!=pointer.ptr;}
        bool operator!=(pointer pointer){return this->ptr!=pointer;}
        bool operator<(ReverseIterator pointer){return this->ptr>pointer.ptr;}
        bool operator<(pointer pointer){return this->ptr>pointer;}
        bool operator>(ReverseIterator pointer){return this->ptr<pointer.ptr;}
        bool operator>(pointer pointer){return this->ptr<pointer;}
        bool operator<=(ReverseIterator pointer){return this->ptr>=pointer.ptr;}
        bool operator<=(pointer pointer){return this->ptr>=pointer;}
        bool operator>=(ReverseIterator pointer){return this->ptr<=pointer.ptr;}
        bool operator>=(pointer pointer){return this->ptr<=pointer;}
    private:
        pointer ptr;
    };
    pointer _start;//数组开端
    pointer _end_of_storage;//数组的最后
    pointer _finish;//数据的最后
    
    
public:
    MyVector();
    MyVector(pointer begin,pointer end);//利用一段迭代器实现构造
    MyVector(size_type _size,const_reference t);//重复_size个t构造
    MyVector(std::initializer_list<_Tp> t);//初始化列表构造
    MyVector(const MyVector& t);//拷贝构造
    ~MyVector();
    
    
    
    //max_size函数无法实现
    bool empty()const;//返回是否为空
    size_type size()const;//返回元素个数
    size_type capacity()const;//返回剩余空间大小
    //以上为vector属性
    
    void swap(MyVector<_Tp>& v);//为拷贝构造服务的交换函数
    void push_back(value_type& value);//向尾部添加元素
    void pop_back();//删除尾部元素
    void reserve(size_type _size);//强制将数组开到_size大小
    void resize(size_type _size,const_reference val=value_type());//强制将数组开到_size大小，并且对所有增加的空间初始化为val。函数缺省值仅在声明时给出
    void shrink_to_fit();//减扩容函数
    pointer insert(pointer position,const_reference value);//插入元素
    pointer insert(pointer position,size_type num,const_reference value);//插入num个元素
    pointer insert(pointer position,pointer first,pointer last);//插入迭代器范围内的元素
    pointer insert(pointer position,std::initializer_list<_Tp> t);//初始化列表插入
    void assign(size_type _size,value_type t);//相当于拷贝，将_size个t赋值给vector
    void assign(std::initializer_list<_Tp> tmp);//用初始化列表进行拷贝
    void erase(pointer position);//删除指定的元素
    void erase(pointer start,pointer end);//删除一段元素，end指向被删除元素之后的位置
    void clear();//清空向量
    //以上为增删操作
    
    reference back();//返回最后一个元素的引用
    reference back()const;//常量类型
    reference front();//返回第一个元素的引用
    reference front()const;
    //以上为获取元素操作
    
    
    pointer find(pointer start,pointer end,const_reference value);//查找范围内元素,返回对应元素的迭代器，没找到返回_finish
    reference at(size_type __n);//返回对应编号的元素
    const_reference at(size_type __n) const;//常量版本
    //以上为查找操作
    
    void operator=(const MyVector<_Tp>& v);//用一个向量给另一个向量赋值
    bool operator==(MyVector<_Tp>& v);//位置与值都相等才返回真，两个向量类型要相同
    bool operator!=(const MyVector<_Tp>& v)const;//同上
    bool operator<(const MyVector<_Tp>& v)const;//以下四个为按字典序比较
    bool operator<=(const MyVector<_Tp>& v)const;
    bool operator>(const MyVector<_Tp>& v)const;
    bool operator>=(const MyVector<_Tp>& v)const;
    reference operator[](size_type __n);//下标重载
    //以上为运算符重载
    
    pointer begin();//返回指向第一个元素的指针
    pointer begin()const;
    pointer end();//返回指向最后一个元素之后的位置的指针
    pointer end()const;
    ReverseIterator rbegin();//反向迭代器头，原来的end()-1
    ReverseIterator rend();//反向迭代器尾，原来的begin()
    ConstReverseIterator crbegin();//常量迭代器
    ConstReverseIterator crend();
    //反向迭代器：自增导致指向容器的前一个元素
    //以上为迭代器操作
    

};

template<class _Tp>
MyVector<_Tp>::MyVector(void):_start(nullptr),_finish(nullptr),_end_of_storage(nullptr){}

template<class _Tp>
MyVector<_Tp>::MyVector(pointer begin,pointer end):_start(nullptr),_finish(nullptr),_end_of_storage(nullptr){
    //为什么不能直接迭代器赋值？还是浅拷贝问题
    while(begin!=end){
        push_back(*begin);
        ++begin;
    }
}

template<class _Tp>
MyVector<_Tp>::MyVector(std::initializer_list<_Tp> t){
    assign(t);
}

template<class _Tp>
MyVector<_Tp>::MyVector(const MyVector& t):_start(nullptr),_finish(nullptr),_end_of_storage(nullptr){
    MyVector tmp(t.begin(),t.end());//调用构造函数创建临时对象
    swap(tmp);//空指针给tmp，可以合法调用析构函数，同时防止浅拷贝
}

template<class _Tp>
MyVector<_Tp>::MyVector(size_type _size,const_reference t){
    assign(_size, t);
}

template<class _Tp>
MyVector<_Tp>::~MyVector(void){
    delete[] _start;//释放掉开辟的空间，_start指向数组头部，所以对_start调用delete[]
    //不可以用delete,否则导致泄漏
    //如果_start为空，也没关系，delete[]会对_start是否为空进行检查
    //但是必须要将这三个指针赋空，因为delete[]只删除指针（将他们变为野指针），而不赋值空。对一个指针调用两次delete[]会导致删除不属于你的程序的指针。
    _start=_finish=_end_of_storage=nullptr;
}



template<class _Tp>
bool MyVector<_Tp>::empty()const{
    return (_start==_finish);//空返回真
}

template<class _Tp>
typename MyVector<_Tp>::size_type MyVector<_Tp>::size()const{
    return _finish-_start;
}

template<class _Tp>
void MyVector<_Tp>::push_back(typename MyVector<_Tp>::value_type& value){
    if(_finish==_end_of_storage){//元素个数和数组大小相等，数组已满，或还没有开数组
        reserve(std::max((size_t)(size()*1.5),(size_t)4));//1.5倍扩容，最小4个
    }
    *_finish=value;//插入元素
    _finish++;//迭代器+1
}

template<class _Tp>
typename MyVector<_Tp>::reference MyVector<_Tp>::operator[](size_type __n){
    assert(__n<size());
    return _start[__n];
}

template<class _Tp>
void MyVector<_Tp>::reserve(typename MyVector<_Tp>::size_type _size){
    if(_size>size()+capacity())//申请空间是否大于剩余空间
    {
        pointer tmp=new value_type[_size];//申请更大的空间
        size_t __size=size();//元素个数，_finish指向的位置
        if(_start!=nullptr)//已经存在MyVector的实例
        {
            for(size_t i=0;i<size();i++)
            {
                tmp[i]=_start[i];//手动复制数据，避免浅拷贝
            }
            delete[] _start;//删除原有指针
        }
        _start=tmp;
        _finish=_start+__size;
        _end_of_storage=_start+_size;//容器尾更新到申请空间的末尾
    }
}

template<class _Tp>
typename MyVector<_Tp>::size_type MyVector<_Tp>::capacity()const{
    return _end_of_storage-_finish;
}

template<class _Tp>
typename MyVector<_Tp>::pointer MyVector<_Tp>::begin()const{
    return _start;
}

template<class _Tp>
typename MyVector<_Tp>::pointer MyVector<_Tp>::begin(){
    return _start;
}

template<class _Tp>
typename MyVector<_Tp>::pointer MyVector<_Tp>::end()const{
    return _finish;
}

template<class _Tp>
typename MyVector<_Tp>::pointer MyVector<_Tp>::end(){
    return _finish;
}

template<class _Tp>
void MyVector<_Tp>::pop_back(){
    assert(_finish>_start);//容器里必须有元素，否则崩溃
    _finish--;//删除只需要尾指针--就可以，下次增加元素会直接覆盖
    shrink_to_fit();//是否需要缩容
}

template<class _Tp>
typename MyVector<_Tp>::reference MyVector<_Tp>::back(){
    return *(_finish-1);
}

template<class _Tp>
typename MyVector<_Tp>::reference MyVector<_Tp>::back()const{
    return *(_finish-1);
}

template<class _Tp>
typename MyVector<_Tp>::reference MyVector<_Tp>::front(){
    return *(_start);
}

template<class _Tp>
typename MyVector<_Tp>::reference MyVector<_Tp>::front()const{
    return *(_start);
}

template<class _Tp>
void MyVector<_Tp>::operator=(const MyVector<_Tp>& v){
    //用一个向量给另一个向量赋值
    this->clear();
    this->reserve(v.size());
    for(auto it=v.begin();it<v.end();it++){
        this->push_back(*it);
    }
}

template<class _Tp>
void MyVector<_Tp>::shrink_to_fit(){
    if(size()<capacity()/4)//元素个数小于数组大小的四分一就缩容
    {
        pointer tmp=new value_type[capacity()/2];//申请一半的空间
        size_type __size=size();//元素个数，_finish指向的位置
        if(_start!=nullptr)//检查有没有实例化
        {
            for(size_type i=0;i<size();i++)
            {
                tmp[i]=_start[i];//手动复制数据，避免浅拷贝
            }
            delete[] _start;//删除原有指针
        }
        _start=tmp;
        _finish=_start+__size;//元素尾迭代器指向_start往后__size个元素
        _end_of_storage=_start+capacity()/2;//容器尾更新到申请空间的末尾
    }
}

template<class _Tp>
bool MyVector<_Tp>::operator==(MyVector<_Tp>& v){
    //位置与值都相等才返回真，两个向量类型要相同
    if(this->size()!=v.size())return 0;//元素个数不等，直接返回false
    else
    {
        for(unsigned i=0;i<this->size();i++)
        {
            if(*((this->begin())+i)!=*(v.begin()+i))//两个向量相同位置的元素不相同，返回false
            {
                return 0;
            }
        }
        return 1;//全程未触发if，返回true
    }
}

template<class _Tp>
bool MyVector<_Tp>::operator!=(const MyVector<_Tp>& v)const{
    if(this->size()!=v.size())return 1;
    else
    {
        for(unsigned i=0;i<this->size();i++)
        {
            if(*((this->begin())+i)!=*(v.begin()+i))//两个向量相同位置的元素不相同，返回true
            {
                return 1;
            }
        }
        return 0;//全程未触发if，返回false
    }
}

template<class _Tp>
bool MyVector<_Tp>::operator<(const MyVector<_Tp>& v)const{
    return std::lexicographical_compare(this->begin(),this->end(),v.begin(),v.end());//对两个容器按字典序排序，严格小于排序
}

template<class _Tp>
bool MyVector<_Tp>::operator>=(const MyVector<_Tp>& v)const{
    return !(*this<v);
    //lexicographical_compare是严格小于排序，所以取补集就是大于等于
}

template<class _Tp>
bool MyVector<_Tp>::operator<=(const MyVector<_Tp>& v)const{
    return (*this<v||*this==v);
}

template<class _Tp>
bool MyVector<_Tp>::operator>(const MyVector<_Tp>& v)const{
    return !(*this<=v);
}

template<class _Tp>
typename MyVector<_Tp>::pointer MyVector<_Tp>::insert(pointer position,const_reference value){
    assert(position>=_start);
    assert(position<=_finish);//保证插入元素的位置有效
    if(_finish==_end_of_storage)//如果数组满了，就扩容
    {
        reserve(size()*1.5);
    }
    
    for(pointer i=end()-1;i>=position;i--){//从后向前，每个元素往后移动一个位置
        *(i+1)=*i;
    }
    *position=value;
    _finish++;
    return position;
}

template<class _Tp>
void MyVector<_Tp>::erase(pointer position){
    assert(position>=_start);//确保合法
    assert(position<=_finish);
    for(pointer i=position;i<end()-1;i++){//所有元素向前移动一个位置
        *i=*(i+1);
    }
    _finish--;//尾指针前移
    shrink_to_fit();//按需缩容
}

template<class _Tp>
void MyVector<_Tp>::erase(pointer start, pointer end){
    assert(start>=_start);
    assert(start<end);//不能等于，因为end指向被删除元素之后的元素
    assert(end<=_finish);
    for(pointer i=end;i<_finish;i++){
        *(i-(end-start))=*i;//所有元素向前移动end-start个格子
    }
    _finish=start;//尾指针指向未被删除的最后一个元素的下一个元素
    shrink_to_fit();//按需缩容
}

template<class _Tp>
typename MyVector<_Tp>::pointer MyVector<_Tp>::find(pointer start, pointer end, const _Tp &value){
    assert(start>=_start);//合法性
    assert(end<=_finish);
    for(pointer i=start;i<end;i++){
        if(*i==value)return i;//找到返回对应迭代器
    }
    return end;//没找到返回容器尾
}

template<class _Tp>
typename MyVector<_Tp>::pointer MyVector<_Tp>::insert(pointer position,size_type num,const_reference value){
    assert(position>=_start);//合法性
    assert(position<=_finish);
    if(num>capacity()){//超容量扩容
        reserve((size()+num)*1.5);
    }
    for(pointer i=_finish-1;i>=position;i--){
        *(i+num)=*i;
    }
    for(pointer i=position;i<position+num;i++){
        *i=value;
    }
    _finish+=num;
    return position;
}

template<class _Tp>
typename MyVector<_Tp>::pointer MyVector<_Tp>::insert(pointer position,pointer first,pointer last){
    size_type new_size=last-first;
    size_type old_distance=position-_start;//当发生扩容，原有迭代器失效，需要重新分配
    if(new_size>capacity()){
        reserve((size()+new_size)*1.5);
    }
    for(pointer i=_finish-1;i>=_start+old_distance;i--){
        *(i+new_size)=*i;
    }
    for(pointer i=_start+old_distance;i<_start+old_distance+new_size;i++)
    {
        *i=*(first++);
    }
    _finish+=new_size;
    return position;
}

template<class _Tp>
typename MyVector<_Tp>::pointer MyVector<_Tp>::insert(pointer position,std::initializer_list<_Tp> t){
    size_type new_size=t.size();
    size_type old_distance=position-_start;//当发生扩容，原有迭代器失效，需要重新分配
    if(new_size>capacity()){
        reserve((size()+new_size)*1.5);
    }
    for(pointer i=_finish-1;i>=_start+old_distance;i--){
        *(i+new_size)=*i;
    }
    size_type cnt=0;
    for(pointer i=_start+old_distance;i<_start+old_distance+new_size;i++,cnt++)
    {
        *i=*(t.begin()+cnt);
    }
    _finish+=new_size;
    return position;
}

template<class _Tp>
typename MyVector<_Tp>::reference MyVector<_Tp>::at(size_type __n){
    assert(__n<size());
    return (*this)[__n];
}

template<class _Tp>
typename MyVector<_Tp>::const_reference MyVector<_Tp>::at(size_type __n)const{
    assert(__n<size());
    return (*this)[__n];
}

template<class _Tp>
void MyVector<_Tp>::resize(size_type _size,const_reference val){
    if(_size>size()+capacity()){//不够大扩容
        reserve(_size);
        while(_finish<_end_of_storage){
            *_finish++=val;
        }
    }
    else{
        _finish=_finish+_size;
        shrink_to_fit();
    }
}

template<class _Tp>
void MyVector<_Tp>::clear(){
    _finish=_start;
    shrink_to_fit();
}

template<class _Tp>
typename MyVector<_Tp>::ReverseIterator MyVector<_Tp>::rbegin(){
    ReverseIterator pointer=_finish-1;//返回指向尾部元素的反向迭代器
    return pointer;
}

template<class _Tp>
typename MyVector<_Tp>::ReverseIterator MyVector<_Tp>::rend(){
    ReverseIterator pointer=_start-1;//返回指向头部元素的前一个元素的反向迭代器
    return pointer;
}

template<class _Tp>
typename MyVector<_Tp>::ConstReverseIterator MyVector<_Tp>::crend(){
    ConstReverseIterator pointer=_start-1;//返回指向头部元素的前一个元素的反向迭代器
    return pointer;
}

template<class _Tp>
typename MyVector<_Tp>::ConstReverseIterator MyVector<_Tp>::crbegin(){
    ConstReverseIterator pointer=_finish-1;//返回指向尾部元素的反向迭代器
    return pointer;
}

template<class _Tp>
void MyVector<_Tp>::swap(MyVector<_Tp> &v){
    std::swap(_start,v._start);
    std::swap(_finish,v._finish);
    std::swap(_end_of_storage,v._end_of_storage);
}

template<class _Tp>
void MyVector<_Tp>::assign(size_type _size,value_type t){
    MyVector<_Tp> tmp;
    for(size_type i=0;i<_size;i++){
        tmp.push_back(t);
    }
    delete[] _start;
    _start=_finish=_end_of_storage=nullptr;
    swap(tmp);//深拷贝
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
template<class _Tp>
void MyVector<_Tp>::assign(std::initializer_list<_Tp> tmp){
    MyVector<_Tp> t;//临时对象
    const _Tp* _=tmp.begin();
    _Tp* it=(_Tp*)_;
    for(;it<tmp.end();it++){
        t.push_back(*it);
    }
    delete[] _start;
    _start=_finish=_end_of_storage=nullptr;
    swap(t);
}

#pragma GCC diagnostic pop

#endif /* MyVector_h */
