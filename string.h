#pragma once
#include <iostream>
class string
{
public:
    string();
    string(const char* s);
    explicit string (unsigned int size_);
    string(const string& s);
    string(string&& s);

    ~string();

    char operator[](int i) const;
    char& operator[](int i);

    char back();

    string& operator=(const string& s);
    string& operator=(int64_t number);
    string& operator=(string&& s);

    string& operator +=(const string& s);
    string operator+(const string& s) const;

    bool operator ==(const string& s) const;
    bool operator != (const string& s) const;
    bool operator<(const string& s) const;
    bool operator >(const string& s) const;
    bool operator >=(const string& s) const;
    bool operator <= (const string& s) const;

    bool is_polindrom();

    const char* c_str() const;
    char* data();
    char* find(const char* key);

    uint64_t count(char ch);
    uint64_t size() const;
    uint64_t capacity();

    int64_t to_number();

    void reserve(uint64_t size);
    void push_back(char ch);
    void reverse();
    void resize(uint size_);
    void insert(char ch,int index);
    void replace(const char* s1,const char* s2);
    bool compare(const char* s1,int left,int right);
    bool compare(const char* s1, const char* s2);
    uint64_t strlen(const char* s);

    char* array; //здесь хранится наша строка
    uint64_t length;//здесь хранится длина нашей строки
    uint64_t copacity_;//здесь хранится вместимость строки(сколько символов в ней может храниться)
};

std::ostream& operator<<(std::ostream& out, const string& s);
std::istream& operator>>(std::istream& in, string& s);
