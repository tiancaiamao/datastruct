#ifndef POOL_ALLOC_H
#define POOL_ALLOC_H
//这是一个自定义的allocator实现.
//不同于默认的allocator使用低级操作,每次一个对象的申请
//使用了内存池方式实现
//此文件无法用于大于8K的对象的allocate

template <class T>
class pool_alloc
{
    struct Link{Link* next;};       //分配内存按Link分配.Link其实是一个指针,相当于void*,其所指向的空间的大小是sizeof(T)
    struct Chunk                    //申请内存按Chunk申请,大小是8K....
    {
        enum{size=8*1024-sizeof(char)-sizeof(Chunk*)};       //一次分配8k的内存
        char mem[size];
        Chunk* next;
    };
    Chunk* chunks;
    Link* head;                             //head是始终指向下一个可用的位置
    pool_alloc(pool_alloc&);          //禁用系统自提供的拷贝构造函数
    void operator=(pool_alloc&);      //禁用系统自提供的赋值函数

    void grow();                    //私有成员用于实现扩大的
public:
    typedef T                value_type;
    typedef size_t           size_type;
    typedef ptrdiff_t        difference_tyre;
    typedef T*               pointer;
    typedef const T*         const_pointer;
    typedef T&               reference;
    typedef const T&         const_reference;

    pool_alloc():head(0),chunks(0){}
    pointer allocate(size_type n,const void* hint=0)
    {
        if(head==0) grow();
        Link* p=head;
        for(int i=0;i<n;i++)
            head=head->next;
        return reinterpret_cast<pointer>(p);
    }
    void deallocate(pointer p,size_type n)      //有待修改
    {
        if(n==1)
        {
            Link* b=reinterpret_cast<Link*>(p);
            b->next=head;
            head=b;
        }
    }
    ~pool_alloc()
    {
        Chunk* temp=chunks;
        while(chunks)
        {
            temp=chunks->next;
            delete chunks;
            chunks=temp;
        }
    }
    void construct(pointer p,const T& val){new (p) T(val);}
    void destroy(pointer p){p->~T();}
};
template <class T>
void pool_alloc<T>::grow()                 //新增一个Chunk.由chunks指向新的Chunk,并把head指向新的可用空间
{
        Chunk* p=new Chunk;
        p->next=chunks;
        chunks=p;

        int temp=sizeof(T);
        int esize=sizeof(Chunk)/temp;
        char* start=chunks->mem;
        char* end=start+esize-1;

        for(char* p=start;p<end;p+=temp)       //把Link*串成一条链
            reinterpret_cast<Link*>(p)->next=reinterpret_cast<Link*>(p+temp);
        reinterpret_cast<Link*>(end)->next=0;
        head=reinterpret_cast<Link*>(start);
}
#endif // POOL_ALLOC_H
