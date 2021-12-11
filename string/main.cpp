#include <iostream>

class string
{
public:
    //конструктор от указателя на char(строки в стиле языка Си).
    //позволяет создать объект строки из си-строки
    //данный конструктор может быть вызван неявно для конвертации си-строки в string
    string(const char* s)
    {
        length = strlen(s);
        array = new char[length+1];
        for(uint64_t i = 0;i<length;i++)
        {
            array[i] = s[i];
        }
    }
    //конструктор от строки. Позволяет создать строку из другой строки
    //конструктор с одним параметром еще называют конструктором копирования
    string(const string& s) : string(s.c_str())
    {
        //тело конструктора ничего не содержит, потому что этот конструктор
        //вызывает конструктор от указателя на char
    }
    //перегрузка оператора [] для константной строки
    //возвращает копию символа, а значит его нельзя будет поменять снаружи
    char operator[](int i) const
    {
        return array[i];
    }
    //перегрузка оператора [] для неконстантной строки
    //возвращает указатель на символ, а значит этот символ можно изменить снаружи
    char& operator[](int i)
    {
        return array[i];
    }
    //оператор присваивания для нашей строки. Вызывается когда мы хотим
    //что-то положить в уже созданную строку
    string& operator=(const string& s)
    {
        //если в нашей строке недостаточно места,
        //мы выделяем новый кусок памяти достаточного размера
        if(s.copacity_ <= this->size())
        {
            delete [] array;
            this->copacity_ = s.size()+1;
            array = new char[s.size()+1];
        }
        this->length = s.size();
        for(uint64_t i = 0;i<=s.size()+1;i++)
        {
            array[i] = s[i];
        }
        return *this;
    }

    string& operator +=(const string& s)
    {
        //если недостаточно памяти, мы расширяем строку
        if(this->copacity() <= s.size()+this->size())
        {
            this->copacity_ = s.size()+this->size()+1;
            char* buffer = new char[this->copacity_];
            for(uint64_t i = 0;i<length;i++)
            {
                buffer[i] = array[i];
            }
            delete [] array;
            array = buffer;
        }
        for(uint64_t i = length; i < length+s.size();i++)
        {
            array[i] = s[i-length];
        }
        this->length = s.size()+this->size();
        return *this;
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
    ~string()
    {
        delete [] array;
    }
    uint64_t size() const
    {
        return length;
    }
    uint64_t copacity()
    {
        return copacity();
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

int main()
{
    string s = "251";
    s += "5";
    std::cout << s << std::endl;
    std::cout << "153";
    return 0;
}
