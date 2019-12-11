#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cctype>

template <class T>
std::string get_parametrs(T&& param)
{
    std::stringstream s;
    s << param;
    return s.str();
}

template <class... Args>
std::string format(const std::string & s, Args&&... args)
{
    std::vector<std::string> param = {get_parametrs(std::forward<Args>(args))...};
    std::stringstream str_fromat;
    for(size_t i=0; i<s.size(); i++)
    {

        if(s[i] == '}')
        {
            throw std::runtime_error("Brackets can not use within context");
        }
        else if(s[i] == '{')
        {
            int tmp_num = 0;
            i++;
            for(i; s[i]!='}'; i++)
            {
                if(s[i] > '9' || s[i] < '0')
                {
                    throw std::runtime_error("Incorrect data in brackets");
                }

                tmp_num *= 10;
                tmp_num += s[i] - '0';
            }
            if(tmp_num >= param.size())
                throw std::runtime_error("Incorrect data in brackets");
            str_fromat << param[tmp_num];

        }
        else
        str_fromat << s[i];
    }

    return str_fromat.str();
}
