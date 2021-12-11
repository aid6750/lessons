#include <cmath>
#include <thread>
#include "string.h"
string::string()
{
    array = nullptr;
    length = 0;
    copacity_ = 0;
}
string::string(const char* s)
{
    length = strlen(s);
    array = new char[length+1];
    copacity_ = length+1;
    for(uint64_t i = 0;i<length;i++)
    {
        array[i] = s[i];
    }
}
string::string (uint size_)
{
    copacity_ = size_+1;
    array = new char[copacity_];
    length = 0;
}
string::string(const string& s) : string(s.c_str())
{
    //тело конструктора ничего не содержит, потому что этот конструктор
    //вызывает конструктор от указателя на char
}
string::string(string&& s)
{
    array = s.array;
    s.array = nullptr;
    length = s.length;
    copacity_ = s.copacity_;
}
string::~string()
{
    if(array != nullptr)
        delete [] array;
}

//перегрузка оператора [] для константной строки
//возвращает копию символа, а значит его нельзя будет поменять снаружи
char string::operator[](int i) const
{
    if(i >= 0)
        return array[i];
    else
        return array[length+i];
}
//перегрузка оператора [] для неконстантной строки
//возвращает указатель на символ, а значит этот символ можно изменить снаружи
char& string::operator[](int i)
{
    if(i >= 0)
        return array[i];
    else
        return array[length+i];
}
//оператор присваивания для нашей строки. Вызывается когда мы хотим
//что-то положить в уже созданную строку
string& string::operator=(const string& s)
{
    //если в нашей строке недостаточно места,
    //мы выделяем новый кусок памяти достаточного размера
    if(this->copacity_ <= s.size())
    {
        delete [] array;
        this->copacity_ = s.size()+1;
        array = new char[s.size()+1];
    }
    this->length = s.size();
    for(uint64_t i = 0;i<=s.size();i++)
    {
        array[i] = s[i];
    }
    return *this;
}

string& string::operator=(int64_t number)
{
    int digits = 1;
    int copy_number = number;
    while(copy_number / 10 > 0)
    {
        copy_number /=10;
        digits++;
    }
    copacity_ = digits+1;
    length = digits;
    if(array != nullptr)
    {
        delete [] array;
    }
    array = new char[copacity_];
    for(int i = length-1;i >= 0;i--)
    {
        array[i] = (number%10)+'0';
        number /= 10;
    }
    return *this;
}
string& string::operator=(string&& s)
{
    if(array != nullptr)
        delete [] array;
    array = s.array;
    s.array = nullptr;
    length = s.length;
    copacity_ = s.copacity_;
    return *this;
}
string& string::operator +=(const string& s)
{
    //если недостаточно памяти, мы расширяем строку
    if(this->copacity_ <= s.size()+this->size())
    {
        this->copacity_ = 2*(s.size()+this->size()+1);
        //запрашиваем область памяти достаточного размера
        char* buffer = new char[this->copacity_];
        //копируем в новую область памяти старую строку
        for(uint64_t i = 0;i<length;i++)
        {
            buffer[i] = array[i];
        }
        //удаляем старую строку
        delete [] array;
        //старое имя строки ссылаем на новый участок памяти
        array = buffer;
    }
    for(uint64_t i = length; i < length+s.size();i++)
    {
        array[i] = s[i-length];
    }
    this->length = s.size()+this->size();
    return *this;
}
//оператор + выразили через +=, чтоб избежать лишних копирований строки
string string::operator+(const string& s) const
{
    string s1 = *this;
    return s1+= s;
}
bool string::operator ==(const string& s) const
{
    if(s.size() != this->size())
        return false;

    for(uint64_t i = 0; i < s.size();i++)
    {
        if(s[i] != array[i])
            return false;
    }

    return true;
}

bool string::operator != (const string& s) const
{
    return !(*this == s);
}

//определяем оператор < и через него выражаем остальные операторы
bool string::operator<(const string& s) const
{
    if(this->size() < s.size())
        return true;
    if(this->size() > s.size())
        return false;

    for(uint64_t i = 0; i < s.size();i++)
    {
        if(s[i] < array[i])
            return true;
    }

    return false;
}

bool string::operator >(const string& s) const
{
    return (s < *this);
}

bool string::operator >=(const string& s) const
{
    return !(s < *this);
}

bool string::operator <= (const string& s) const
{
    return ! (s > *this);
}

//возвращает си-строку (данную строчку нельзя будет изменять)
const char* string::c_str() const
{
    return const_cast<const char*>(array);
}
//возвращает строку, которую можно менять
char* string::data()
{
    return array;
}
uint64_t string::size() const
{
    return length;
}
uint64_t string::capacity()
{
    return copacity_;
}

void string::reserve(uint64_t size)
{
    copacity_ = size;
    if(array != nullptr)
    {
        char* tmp = new char[copacity_];
        for(uint64_t i = 0;i< this->length;i++)
            tmp[i] = array[i];
        delete [] array;
        array = tmp;
    }
    else
    {
        array = new char[copacity_];
    }
}
void string::resize(uint size_)
{
    if(size_ < copacity_)
    {
        length = size_;
        array[size_+1] = '\0';
    }
    else
    {
        copacity_ = size_*2;
        char* tmp = new char[copacity_];
        for(uint64_t i = 0;i< this->length;i++)
            tmp[i] = array[i];
        delete [] array;
        array = tmp;
        length = size_;
        array[length] = '\0';
    }
}

void string::push_back(char ch)
{
    if(copacity_ <= length+1)
    {
        copacity_ *= 2;
        char* tmp = new char[copacity_*2];
        for(uint i= 0;i<length;i++)
        {
            tmp[i] = array[i];
        }
        delete [] array;
        array = tmp;
        array[length] = ch;
        length++;
    }
    array[length] = ch;
    length++;
}
void string::reverse()
{
    for(uint i = 0;i<length/2;i++)
    {
        std::swap(array[i],array[length-i-1]);
    }
}

bool string::is_polindrom()
{
    for(uint i = 0;i<length/2;i++)
    {
        if(array[i] != array[length-i-1])
            return false;
    }
    return true;
}

uint64_t string::count(char ch)
{
    uint64_t counter = 0;
    for(uint i = 0;i<length;i++)
    {
        if(array[i] == ch)
            counter++;
    }
    return counter;
}

char string::back()
{
    return array[length-1];
}

int64_t string::to_number()
{
    int64_t number = 0;
    //-139 = 100+30+9
    //1 * 100 + 3*10 +9 * 1
    int j = 0;
    for(int i = length-1; i >= 0;i--)
    {
        if(array[j] == '-' or array[j] == '+')
        {
            j++;
            continue;
        }
        number += (array[j]-'0')*pow(10,i);
        j++;
    }
    if(array[0] == '-' )
        number = -number;
    return number;
}
void string::insert(char ch,int index)
{
    if(this->copacity_ > this->length+1)
    {
        for(int i = this->length; i > index ; i--)
        {
            array[i] = array[i-1];
        }
        array[index] = ch;
    }
    else
    {
        char* tmp = new char[(length+1)*2];
        for(int i = 0; i < index;i++)
        {
            tmp[i] = array[i];
        }
        tmp[index] = ch;
        for(uint i = index+1; i <= this->length; i++)
        {
            tmp[i] = array[i-1];
        }
        delete [] array;
        array = tmp;
    }
}
char* string::find(const char* key)
{
    uint L1 = strlen(key);
    for(uint i = 0;i<= this->length-L1;i++)
    {
        if(compare(key,i,i+L1))
        {
            return array + i;
        }
    }
    return nullptr;
}
void string::replace(const char* s1,const char* s2)
{
    uint L1 = strlen(s1);
    uint L2 = strlen(s2);
    if(L1 == L2)
    {
        if(compare(s1,s2))
            return ;
        char* piece = this->find(s1);
        while(piece != nullptr)
        {
            int i = piece - array;
            for(uint j = 0 ;j < L1;j++)
            {
                array[i+j] = s2[j];
            }
            piece = this->find(s1);
        }
    }
    if(L1 > L2)
    {
        int diff = L1 - L2;
        char* piece = this->find(s1);
        while(piece != nullptr)
        {
            int i = piece - array;
            uint j = 0;
            for(j = 0 ;j < L2;j++)
            {
                array[i+j] = s2[j];
            }
            for(uint k = j; i+k < length-diff;k++)
            {
                array[i+k] = array[i+k+diff];
            }
            array[length-diff] = '\0';
            piece = this->find(s1);
        }
    }
    if(L1 < L2)
    {
        int diff = L2 - L1;
        char* piece = this->find(s1);
        while(piece != nullptr)
        {
            char* A = array;
            int i = piece - array;
            for(uint j = 0 ;j < L1;j++)
            {
                array[i+j] = s2[j];
            }
            for(uint j = length+diff; i+j >= i+L1;j--)
            {
                if(this->capacity() <= length+diff)
                {
                    char* tmp = new char[this->capacity()*2];
                    for(uint i = 0;i<this->length;i++)
                    {
                        tmp[i] = array[i];
                    }
                    delete [] array;
                    array = tmp;
                }

                array[i+j] = array[i+j-1];
            }
            piece = string(piece).find(s1);
            std::cout << array << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
}

bool string::compare(const char* s1,int left,int right)
{
    for(int i = 0;i < right-left;i++)
    {
        if(s1[i] != array[i+left])
        {
            return false;
        }
    }
    return true;
}
uint64_t string::strlen(const char* s)
{
    uint64_t t = 0;
    for(int i = 0;s[i] != '\0';i++)
    {
        t++;
    }
    return t;
}

std::ostream& operator<<(std::ostream& out, const string& s)
{
    out << s.c_str();
    return out;
}
std::istream& operator>>(std::istream& in, string& s)
{
    char buffer[256];
    s = buffer;
    return in;
}

bool string::compare(const char* s1,const char* s2)
{
    int L1 = strlen(s1);
    int L2 = strlen(s2);

    if(L1 != L2)
    {
        return false;
    }

    for(int i = 0;i<L1;i++)
    {
        if(s1[i] != s2[i])
            return false;
    }
    return true;
}
