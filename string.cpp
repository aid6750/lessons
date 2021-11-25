#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <cmath>
class string
{
public:
    //конструктор без параметров. Необходим для создания пустой строки
    string()
    {
        array = nullptr;
        length = 0;
        copacity_ = 0;
    }

    //конструктор от указателя на char(строки в стиле языка Си).
    //позволяет создать объект строки из си-строки
    //данный конструктор может быть вызван неявно для конвертации си-строки в string
    string(const char* s)
    {
        length = strlen(s);
        array = new char[length+1];
        copacity_ = length+1;
        for(uint64_t i = 0;i<length;i++)
        {
            array[i] = s[i];
        }
    }
    explicit string (uint size_)
    {
        copacity_ = size_+1;
        array = new char[copacity_];
        length = 0;
    }
    //конструктор от строки. Позволяет создать строку из другой строки
    //конструктор с одним параметром еще называют конструктором копирования
    //данный конструктор будет вызываться при передаче нашей строки в функцию
    //(чтоб та могла создать себе копию нашего объекта)
    string(const string& s) : string(s.c_str())
    {
        //тело конструктора ничего не содержит, потому что этот конструктор
        //вызывает конструктор от указателя на char
    }

    ~string()
    {
        if(array != nullptr)
            delete [] array;
    }

    //перегрузка оператора [] для константной строки
    //возвращает копию символа, а значит его нельзя будет поменять снаружи
    char operator[](int i) const
    {
        if(i >= 0)
            return array[i];
        else
            return array[length+i];
    }
    //перегрузка оператора [] для неконстантной строки
    //возвращает указатель на символ, а значит этот символ можно изменить снаружи
    char& operator[](int i)
    {
        if(i >= 0)
            return array[i];
        else
            return array[length+i];
    }
    //оператор присваивания для нашей строки. Вызывается когда мы хотим
    //что-то положить в уже созданную строку
    string& operator=(const string& s)
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

    string& operator=(int64_t number)
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

    string& operator +=(const string& s)
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
    const string operator+(const string& s) const
    {
        string s1 = *this;
        return s1+= s;
    }
    bool operator ==(const string& s) const
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

    bool operator != (const string& s) const
    {
        return !(*this == s);
    }

    //определяем оператор < и через него выражаем остальные операторы
    bool operator<(const string& s) const
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

    bool operator >(const string& s) const
    {
        return (s < *this);
    }

    bool operator >=(const string& s) const
    {
        return !(s < *this);
    }

    bool operator <= (const string& s) const
    {
        return ! (s > *this);
    }

    //возвращает си-строку (данную строчку нельзя будет изменять)
    const char* c_str() const
    {
        return const_cast<const char*>(array);
    }
    //возвращает строку, которую можно менять
    char* data()
    {
        return array;
    }
    uint64_t size() const
    {
        return length;
    }
    uint64_t capacity()
    {
        return copacity_;
    }

    void reserve(uint64_t size)
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
    void resize(uint size_)
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

    void push_back(char ch)
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
    void reverse()
    {
        for(uint i = 0;i<length/2;i++)
        {
            std::swap(array[i],array[length-i-1]);
        }
    }

    bool is_polindrom()
    {
        for(uint i = 0;i<length/2;i++)
        {
            if(array[i] != array[length-i-1])
                return false;
        }
        return true;
    }

    uint64_t count(char ch)
    {
        uint64_t counter = 0;
        for(uint i = 0;i<length;i++)
        {
            if(array[i] == ch)
                counter++;
        }
        return counter;
    }

    char back()
    {
        return array[length-1];
    }

    int64_t to_number()
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

private:
    uint64_t strlen(const char* s)
    {
        uint64_t t = 0;
        for(int i = 0;s[i] != '\0';i++)
        {
            t++;
        }
        return t;
    }
    char* array; //здесь хранится наша строка
    uint64_t length;//здесь хранится длина нашей строки
    uint64_t copacity_;//здесь хранится вместимость строки(сколько символов в ней может храниться)
};

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


int main()
{
    return 0;
}
