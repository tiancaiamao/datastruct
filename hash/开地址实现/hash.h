#ifndef HASH_H
#define HASH_H

#define KeyType int
#define ValueType int
static const float hash_full_ratio=0.5;    //哈希因子
static const int hash_resize_factor=2;     //增长速度,每次增长把容量扩大原来的hash_resize_factor倍
static const float hash_refresh_ratio=0.25;     //当DELETE占的比例大于此数是调用refresh对DELETE元素物理删除
typedef enum {EMPTY,OCCUPY,DELETE}status;
typedef struct cell     //key-value结构
{
    KeyType key;
    ValueType value;
    status stat;
}cell;
typedef unsigned long (*hashfun_t) (KeyType);  //哈希函数指针
typedef struct
{
    cell* addr;         //首地址
    int currentsize;        //当前hash表内的元素个数
    int tombsize;        //标记为DELETE的个数
    int size;      //hash表大小
    hashfun_t hashfunction;     //hash函数指针
    int prime_offset;      //用于查表得到合适的质数以设置hash表的大小
}hash;
int createhash(hash* h,int defaultsize,hashfun_t hf);
void destroyhash(hash* h);
cell* find(hash* h,KeyType key);
int push(hash* h,KeyType key,ValueType value);
int pop(hash* h,KeyType key);
#endif // HASH_H
