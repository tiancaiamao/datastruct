#ifndef HASH_H
#define HASH_H

#define hash_factor 0.75        //哈希因子
#define hash_increase_factor 2  //哈希表增长因子
#define Elemtype int
#define Keytype int
typedef struct cell
{
    Keytype key;
    Elemtype data;
    int next;       //指针域
}cell;
typedef unsigned long (*hash_t) (Keytype);  //hash函数指针
/*
 *静态链表重分配空间时指针关系不会失效，可以方便地调用realloc函数
 */
typedef struct hash
{
    //hash表部分
    int* table;         //表．表元素是指向buff区的指针.静态链
    int currentsize;    //当前大小
    int totalsize;      //总大小
    hash_t hf;          //哈希函数
    int prime_offset;      //用于查表得到合适的质数以设置hash表的大小
    //buff部分
    cell* buff;         //存储区基地址
    int buffsize;       //存储区总大小
    int buffcurrent;    //存储区当前位置
}hash;
int createhash(hash* h,int size,hash_t hf);
void destroyhash(hash* h);
int insert(hash* h,Keytype key,Elemtype value);
int search(hash* h,Keytype key,Elemtype* value);
int remove1(hash* h,Keytype key);
#endif // HASH_H
