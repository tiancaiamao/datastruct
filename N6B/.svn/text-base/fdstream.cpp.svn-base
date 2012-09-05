#include "fdstream.h"

//缓存类fd_filebuf
//构造函数是调用基类的构造函数
//基类构造函数和open函数是分开的。open函数中需要char*的文件名参数
//而构造函数只有一个默认构造函数。。。这里fd＿filebuf做的事情就是调用基类的默认构造函数
//fd设成一个无效的。调用open方法才能设置成一个有效的

//open函数,fd做参数的
fd_filebuf* fd_filebuf::open(int _fd,std::ios_base::openmode __mode)
{
    fd_filebuf *__ret = NULL;
    if (!this->is_open())
    {
        _M_file.sys_open(_fd, __mode);
        if (this->is_open())
        {
            _M_allocate_internal_buffer();
            _M_mode = __mode;

            // Setup initial buffer to 'uncommitted' mode.
            _M_reading = false;
            _M_writing = false;
            _M_set_buffer(-1);

            // Reset to initial state.
            _M_state_last = _M_state_cur = _M_state_beg;

            // 27.8.1.3,4
            if ((__mode & std::ios_base::ate)
                && this->seekoff(0, std::ios_base::end, __mode)
                == pos_type(off_type(-1)))
                this->close();
            else
                __ret = this;
        }
    }
    return __ret;
}
//open函数,char*做参数的
fd_filebuf* fd_filebuf::open(const char* __s,std::ios_base::openmode __mode)
{
    fd_filebuf *__ret = NULL;
    if (!this->is_open())
    {
        _M_file.open(__s, __mode);
        if (this->is_open())
        {
            _M_allocate_internal_buffer();
            _M_mode = __mode;

            // Setup initial buffer to 'uncommitted' mode.
            _M_reading = false;
            _M_writing = false;
            _M_set_buffer(-1);

            // Reset to initial state.
            _M_state_last = _M_state_cur = _M_state_beg;

            // 27.8.1.3,4
            if ((__mode & std::ios_base::ate)
                && this->seekoff(0, std::ios_base::end, __mode)
                == pos_type(off_type(-1)))
                this->close();
            else
                __ret = this;
        }
    }
    return __ret;
}

//ifdstream类
ifdstream::ifdstream(int _fd,std::ios_base::openmode __mode):_M_buf()
{
    this->init(&_M_buf);
    this->open(_fd,__mode);
}
void ifdstream::open(int _fd,std::ios_base::openmode __mode)
{
    if(!_M_buf.open(_fd,__mode))
        this->setstate(std::ios_base::failbit);
    else
        this->clear();
}
void ifdstream::close()
{
    if(!_M_buf.close())
        this->setstate(std::ios_base::failbit);
}
bool ifdstream::is_open()
{
    return _M_buf.is_open();
}
fd_filebuf* ifdstream::rdbuf()
{
    return &_M_buf;
}

//ofdstream类
ofdstream::ofdstream():_M_buf()
{
    this->init(&_M_buf);
}
ofdstream::ofdstream(int _fd,ios_base::openmode __mode):_M_buf()
{
    this->init(&_M_buf);
    this->open(_fd,__mode);
}
ofdstream::ofdstream(const char* __s,std::ios_base::openmode __mode):_M_buf()
{
    this->init(&_M_buf);
    this->open(__s,__mode);
}
void ofdstream::open(int _fd,std::ios_base::openmode __mode)
{
    if (!_M_buf.open(_fd, __mode | ios_base::out))
        this->setstate(ios_base::failbit);
    else
        this->clear();
}
void ofdstream::open(const char* __s,std::ios_base::openmode __mode)
{
    if(!_M_buf.open(__s,__mode|std::ios_base::out))
        this->setstate(std::ios_base::failbit);
    else
        this->clear();
}
bool ofdstream::is_open()
{
    return _M_buf.is_open();
}
fd_filebuf* ofdstream::rdbuf()
{
    return &_M_buf;
}
void ofdstream::close()
{
    if(!_M_buf.close())
        this->setstate(std::ios_base::failbit);
}
int ofdstream::fileno()
{
    return _M_buf.fd();
}
//fdstream类的成员函数
fdstream::fdstream():_M_buf()
{
    this->init(&_M_buf);
}
fdstream::fdstream(int _fd,std::ios_base::openmode _mode):_M_buf()
{
    this->init(&_M_buf);
    this->open(_fd,_mode);
}
fdstream::fdstream(const char* __s,std::ios_base::openmode _mode):_M_buf()
{
    this->init(&_M_buf);
    this->open(__s,_mode);
}
fd_filebuf* fdstream::rdbuf()
{
    return &_M_buf;
}
bool fdstream::is_open()
{
    return _M_buf.is_open();
}
void fdstream::open(int _fd,std::ios_base::openmode _mode)
{
    if(!_M_buf.open(_fd,_mode))
        this->setstate(std::ios_base::failbit);
    else
        this->clear();
}
void fdstream::open(const char* __s,std::ios_base::openmode _mode)
{
    if(!_M_buf.open(__s,_mode))
        this->setstate(std::ios_base::failbit);
    else
        this->clear();
}
void fdstream::close()
{
    if(!_M_buf.close())
        this->setstate(std::ios_base::failbit);
}
int fdstream::fileno()
{
        return _M_buf.fd();
}
