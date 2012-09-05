#include "hash.h"
#include <stdlib.h>
/*
 *这是一个链式实现的哈希表．其中有二部分table表用于存放指向buff区的指针
 *buff表存放真正的数据．以静态链表方式组织．指针就是int型.
 *保持一个hash因子．当table表太满时就重新分配table表．这也会使buff区重分配
 *使用静态链的原因是:
 *静态链表重分配空间时指针关系不会失效，可以方便地调用realloc函数,这样对buff区的操作就简单一点
 */
//buff区元素的标记．EMPTY表示空，可以放入数据．REAR表示该位置是链尾
#define EMPTY -1
#define REAR -2
//提供一个默认的哈希函数
static unsigned long defaulthash(Keytype key)
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
int createhash(hash* h,int size,hash_t hf)
{
    //table部分的初始化
    h->prime_offset=0;
    h->totalsize=prime_size(size,&h->prime_offset);
    h->table=(int*)malloc(h->totalsize*sizeof(int));    //分配表空间
    if(h->table==NULL)
        return -1;
    int i;
    for(i=0;i<h->totalsize;++i)
        h->table[i]=EMPTY;
    h->currentsize=0;
    h->hf=hf?hf:defaulthash;
    //buff的初始化
    h->buffsize=h->totalsize;
    h->buff=(cell*)malloc(h->buffsize*sizeof(cell));
    if(h->buff==NULL)
        return -1;
    h->buffcurrent=0;
    return 0;
}
void destroyhash(hash* h)
{
    free(h->table);
    free(h->buff);
}
//当哈希表太满时调用此函数
static int rehash(hash* h)
{
    //重新分配table表
    h->totalsize=prime_size(h->totalsize*hash_increase_factor,&h->prime_offset);
    free(h->table);
    h->table=(int*)malloc(h->totalsize*sizeof(int));
    if(h->table==NULL)
        return -1;
    int i;
    for(i=0;i<h->totalsize;++i)
        h->table[i]=EMPTY;
    h->currentsize=0;
    //重新分配buff区
    int oldsize=h->buffcurrent;
    cell* oldbuff=h->buff;
    h->buff=(cell*)malloc(h->buffsize*sizeof(cell));
    h->buffcurrent=0;
    for(i=0;i<oldsize;++i)
    {
        if(oldbuff[i].next!=EMPTY)
        {
            insert(h,oldbuff[i].key,oldbuff[i].data);
        }
    }
    free(oldbuff);
    return 0;
}
int insert(hash* h,Keytype key,Elemtype value)
{
    int pos=(h->hf(key))%h->totalsize;
    if(h->table[pos]==EMPTY)    //hash成功
    {
        h->table[pos]=h->buffcurrent;
        h->buff[h->buffcurrent].data=value;     //插入
        h->buff[h->buffcurrent].key=key;
        h->buff[h->buffcurrent].next=REAR;
        ++h->buffcurrent;
        ++h->currentsize;
    }
    else    //冲突了
    {
        int p=h->table[pos];
        while(h->buff[p].key!=key && h->buff[p].next!=REAR)
        {             
            p=h->buff[p].next;
        }
        if(h->buff[p].key==key)      //这个key在表中已经存在了
        {
            h->buff[p].data=value;
            return -1;
        }
        h->buff[p].next=h->buffcurrent;
        p=h->buff[p].next;
        h->buff[p].next=REAR;
        h->buff[p].key=key;
        h->buff[p].data=value;
        ++h->buffcurrent;
        ++h->currentsize;
    }
    //可能发生缓存不够重新分配
    if(h->buffcurrent==h->buffsize)
    {
        h->buffsize*=2;
        h->buff=realloc(h->buff,h->buffsize*sizeof(cell));
        if(h->buff==NULL)
            abort();
    }
    //可能由于哈希表太满而rehash
    if(h->totalsize*hash_factor < h->currentsize)
    {
        rehash(h);
    }
    return 0;
}
//成功返回0,用value返回值．失败返回-1
int search(hash* h,Keytype key,Elemtype* value)
{
    int pos=(h->hf(key))%h->totalsize;
    int p=h->table[pos];
    if(p==EMPTY)    //key在table表中不存在
        return -1;
    while(p!=REAR)
    {
        if(h->buff[p].key==key)
        {
            *value=h->buff[p].data;  //打到
            return 0;
        }
        p=h->buff[p].next;
    }
    return -1;
}
/*
 *真恶心．C语言居然不支持函数名重载．remove函数名和stdio库里的一个remove冲突了．暂时命名remove1
 *这个函数的作用是删除key所在的项．如果key不存在，返回-1表出错．
 *删除不是真的物理删除．只是把指针针向下一个．这样就会有产生无法使用的空间．
 *不过不用担心，rehash函数会重建buff区,那时就会把空间回收了
 */
int remove1(hash* h,Keytype key)
{
    int pos=(h->hf(key))%h->totalsize;
    if(h->table[pos]==EMPTY)
        return -1;
    int p=h->table[pos];
    if(h->buff[p].key==key)         //因为是不带表头的链，如果删除的是表头结点就得特殊处理
    {
        h->table[pos]=h->buff[p].next;
        h->buff[p].next=EMPTY;
        --h->currentsize;
        return 0;
    }
    int q=h->buff[p].next;        //p指向的是待删结点前一结点 q指向待删结点
    while( q!=REAR && h->buff[q].key!=key)       //删除非头结点
    {
        p=q;
        q=h->buff[q].next;
    }
    if(q==REAR)     //没找到
        return -1;
    h->buff[p].next=h->buff[q].next;
    h->buff[q].next=EMPTY;
    --h->currentsize;
    return 0;
}











