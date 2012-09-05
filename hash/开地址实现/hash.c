#include "hash.h"
#include <stdlib.h>
static unsigned long defaulthash(KeyType key)   //文件作用域static
{
    unsigned long ret=0;
    int len=sizeof(key);
    const char* p=(const char*)&key;
    while(--len) ret = (ret << 5) - ret + *p++;
    return ret;
}
/*
 *prime_size返回的是一个大于size的最小质数6i+1,6i-1...通过查表得到
 *这个返回值用于设置hash表的大小
 *注意，hash表是自动增长的。开始传入的大小参数只是一个参考大小，并不一定等于hash->size
 */
static int prime_size (int size, int *prime_offset)
{
  static const int primes[] = {
    13, 19, 29, 41, 59, 79, 107, 149, 197, 263, 347, 457, 599, 787, 1031,
    1361, 1777, 2333, 3037, 3967, 5167, 6719, 8737, 11369, 14783,
    19219, 24989, 32491, 42257, 54941, 71429, 92861, 120721, 156941,
    204047, 265271, 344857, 448321, 582821, 757693, 985003, 1280519,
    1664681, 2164111, 2813353, 3657361, 4754591, 6180989, 8035301,
    10445899, 13579681, 17653589, 22949669, 29834603, 38784989,
    50420551, 65546729, 85210757, 110774011, 144006217, 187208107,
    243370577, 316381771, 411296309, 534685237, 695090819, 903618083,
    1174703521, 1527114613, 1837299131, 2147483647
  };
  int tablesize=sizeof(primes)/sizeof(int);
  while((*prime_offset)<tablesize && primes[*prime_offset]<size)
      ++(*prime_offset);
  if(*prime_offset==tablesize)      //如果hash表太大无法分配了，简单的调用abort
      abort();
  return primes[*prime_offset];
}
int createhash(hash* h,int defaultsize,hashfun_t hf)
{
    h->prime_offset=0;
    h->size=prime_size(defaultsize,&h->prime_offset);
    if((h->addr=(cell*)malloc(sizeof(cell)*h->size))==0)
        return 1;
    h->hashfunction=hf?hf:defaulthash;
    h->currentsize=0;
    h->tombsize=0;
    int i;
    for(i=0;i<h->size;++i)          //初始化为空
        (h->addr+i)->stat=EMPTY;
    return 0;
}
void destroyhash(hash* h)
{
    free(h->addr);
}
/*
 *增长过程，把原来表的size和prime_size变动了。并更新了存储空间。currentsize不变,tombsize清零
 */
static int grow(hash* h)
{
    int oldsize=h->size;
    h->size=prime_size(oldsize*hash_resize_factor,&h->prime_offset);    //更新size...函数调用prime_size还会自动更新prime_offset
    cell* oldaddr=h->addr;
    if((h->addr=(cell*)malloc(h->size*sizeof(cell)))==0)     //更新存储空间
        return 1;
    int i;
    for(i=0;i<h->size;++i)
        (h->addr+i)->stat=EMPTY;    //初始化新表
    h->currentsize=0;               //currentsize计数清零
    for(i=0;i<oldsize;++i)          //把原来表的数据转到新存储空间
    {
        if((oldaddr+i)->stat==OCCUPY)
           push(h,(oldaddr+i)->key,(oldaddr+i)->value);     //这里会更新currentsize计数
    }
    free(oldaddr);      //销毁原来的存储空间
    h->tombsize=0;         //tomb计数清0
    return 0;
}
static void refresh(hash* h)    //刷新hash表，把标记为DELETE的元素物理删除(弄成EMPTY)
{
    int i;
    for(i=0;i<h->size;++i)
    {
        if((h->addr+i)->stat==DELETE)
           (h->addr+i)->stat=EMPTY;
        if((h->addr+i)->stat==OCCUPY && h->hashfunction((h->addr+i)->key)!=i)
        {
            (h->addr+i)->stat=EMPTY;
            --h->currentsize;           //很需要注意的一点是push会更新currentsize计数
            push(h,(h->addr+i)->key,(h->addr+i)->value);
        }
    }
    h->tombsize=0;
}
/*
 *查找函数,成功返回结果指针，失败返回插入位置指针
 *这个函数是后面函数的基础。插入，删除都会先调用这个函数找到位置
 *     EMPTY 返回cell*  没找到，返回插入位置
 *     OCCUPY  key相等　找到，返回结果位置
 *             key不等　查找相邻位置
 *     DELETE  　　　　　查找相邻位置
 */
cell* find(hash* h,KeyType key)
{
    unsigned long locate=h->hashfunction(key)%h->size;
    cell* ret=h->addr+locate;
    while(ret->stat==DELETE || (ret->stat==OCCUPY&&ret->key!=key))
        ret=h->addr+(++locate)%h->size;
    return ret;     //返回要么是一个空位置，要么找到了
}
int push(hash* h,KeyType key,ValueType value)
{
    cell* p=find(h,key);    //找到插入位置
    if(p->stat==EMPTY)      //插入新的key-value对
    {
        p->key=key;
        p->value=value;
        p->stat=OCCUPY;
        ++h->currentsize;
    }
    else    //更新原来key对应的value
    {
        p->value=value;
    }
    /*
     *如果元素过多，hash表性能会降低。通过重新分配更大空间，使哈希因子在一定范围内
     *这样就可以保证性能了.下面就是扩大hash表
     */
    if(h->currentsize>h->size*hash_full_ratio)
        return grow(h);
    return 0;
}
/*
 *删除策略是标记法。因为开地址法哈希表物理删除会产生问题。有二种方案解决，一种是仍用物理删除，不过每次删除过后要刷新
 *另一种是标记法。而标记也会带来问题，即DELETE标记位置的空间是无法用的。
 *经过多次删除之后就会有很多"死空间"。需要采用某种方法每隔一定时间做物理删除.refresh函数就是做这件事的
 *第一种方案的劣势是删除时花的时间长，第二种方案删除很快。
 *这里用第二种方法
 */
int pop(hash* h,KeyType key)
{
    cell* p=find(h,key);
    if(p->stat==EMPTY)      //key不存在，无法pop
        return -1;
    p->stat=DELETE;
    --h->currentsize;
    ++h->tombsize;
    if(h->tombsize>hash_refresh_ratio*h->size)    //如果死空间过多，就刷新进行物理删除
        refresh(h);
    return 0;
}


