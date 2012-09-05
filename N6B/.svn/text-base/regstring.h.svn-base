#ifndef REGSTRING_H
#define REGSTRING_H
#include <string>
#include <algorithm>

//文件继承自std::string
//在Effective C++上说，这种方式不好．因为std::string并没提供一个virtual的析构函数．它并没准备被继承的
//考虑这种情况:一个string的指针，指向regstring对象．然后调用delete．这时因为没有virtual，就会造成部分析构
//这是memory　leak的一种情况．不过，这里regstring没有自己的数据成员，并不会造成泄露
namespace N6B
{
    class regstring:public std::string   //regstring is-a string
    {
    public:
        regstring(const std::string&);
        regstring(const char*);
        bool match(const std::string&) const;
        bool match(const char*) const;
    private:
        template <class InputIterator1,class InputIterator2>
        bool m_match(InputIterator1 i,InputIterator1 iend,InputIterator2 j,InputIterator2 jend) const
        {
            while(i!=iend || j!=jend)
            {
                if(*i==*j || *i=='?')       //?或匹配
                {
                    ++i;
                    ++j;
                }
                else if(*i== '*')       //*号匹配任意多个
                {
                    ++i;
                    if(i==iend)           //前面都匹配了，而最后一个是*
                        return true;
                    j=std::find(j,jend,*i);      //j向前滑
                    while(j!=jend)                 //只要没到最后，都可以再次滑
                    {
                        if(m_match(i,iend,j,jend))
                            return true;  //递归匹配,如果匹配了就是匹配
                        else
                            j=std::find(++j,jend,*i);     //j再前滑
                    }
                    return false;
                }
                else                    //一旦发生不匹配，返回false
                    return false;
            }
            return true;
        }
    };
}
#endif // REGSTRING_H
