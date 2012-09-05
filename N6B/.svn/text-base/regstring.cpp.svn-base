#include "regstring.h"
#include <cstring>
using namespace N6B;

regstring::regstring(const std::string& s):std::string(s){}
regstring::regstring(const char* s):std::string(s){}

bool regstring::match(const std::string& s) const
{
    return m_match(begin(),end(),s.begin(),s.end());
}
bool regstring::match(const char* s) const
{
    return m_match(begin(),end(),s,s+strlen(s));
}
