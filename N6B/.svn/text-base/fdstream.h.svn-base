#ifndef FDSTREAM_H
#define FDSTREAM_H

#include <streambuf>
#include <fstream>

//自定义的缓存类继承自filebuf,就是包装一下而已
//实现上提供用fd构造的构造函数
//提供protected接口的fd()返回文件描述符，供上层调用

class fd_filebuf:public std::filebuf
{
public:
    //open函数,重载基类的open,基类的open是用char*构造，这里重载成用int型的文件描述符构造
    fd_filebuf* open(int _fd, std::ios_base::openmode __mode);
    //open函数,因为上面一个open函数把基类的open函数覆盖了，所以要再提供
    fd_filebuf* open(const char* __s,std::ios_base::openmode __mode);
    int fd(){return _M_file.fd();}               //返回文件描述符，供上层调用._M_file是filebuf的保护成员，类型是basic_file实际是一个FILE结构的封装
};

class ifdstream:public std::istream
{
    //私有成员缓存
    fd_filebuf _M_buf;
public:
    //默认构造函数就是初始化缓存
    ifdstream():_M_buf()
    {
        this->init(&_M_buf);         //这个init函数一级一级继承过来的。真正追踪到basic_ios类的init
    }
    //用文件描述符做构造函数
    explicit ifdstream(int _fd,std::ios_base::openmode __mode=std::ios_base::in);
    ~ifdstream(){}          //析构成员不做事，事情会由缓存自己完成
    void open(int _fd,std::ios_base::openmode __mode=std::ios_base::in);       //提供open函数
    void close();
    bool is_open();
    fd_filebuf* rdbuf();
};

//ofdstream类
class ofdstream:public std::ostream
{
//私有成员buf
    fd_filebuf _M_buf;
public:
    //默认构造函数
    ofdstream();
    //用fd构造ofdstream的函数
    explicit ofdstream(int _fd,std::ios_base::openmode __mode = ios_base::out|ios_base::trunc);
    //用字符串常量做构造函数
    explicit ofdstream(const char* __s,std::ios_base::openmode __mode = ios_base::out|ios_base::trunc);
    //open函数，这里为fd做重载的
    void open(int _fd,ios_base::openmode __mode = ios_base::out | ios_base::trunc);
    //open函数，和ofstream的open一样的
    void open(const char* __s,std::ios_base::openmode __mode=std::ios_base::out|std::ios_base::trunc);
    bool is_open();
    fd_filebuf* rdbuf();
    void close();
    int fileno();
};
//fdstream类
class fdstream:public std::iostream
{
    fd_filebuf _M_buf;
public:
    //默认构造函数
    fdstream();
    //char*构造
    fdstream(const char* __s,std::ios_base::openmode _mode=std::ios_base::in|std::ios_base::out);
    //文件描述符构造
    fdstream(int _fd,std::ios_base::openmode _mode=std::ios_base::in|std::ios_base::out);
    bool is_open();
    fd_filebuf* rdbuf();
    void open(const char* __s,std::ios_base::openmode _mode);
    void open(int _fd,std::ios_base::openmode _mode);
    void close();
    int fileno();
};

#endif // FDSTREAM_H
