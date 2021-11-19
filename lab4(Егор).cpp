#include <iostream>


int f(char* s,int length)
{
    int counter = 0;
    int counter_chars = 0;
    for(int i =0; s[i] != '\0'; i++)
    {
        if(s[i] != ' ' and (s[i+1] == ' ' or s[i+1] == '\0'))
        {
            counter_chars++;
            if(counter_chars < length)
                counter++;
            counter_chars = 0;
        }
        else if(s[i] != ' ' and s[i+1] !=' ')
        {
            counter_chars++;
        }

    }

    return counter;
}

int main(void)
{
    char* string;
    std::cout << "сколько символов в строке? ";
    int cin;
    int length;
    std::cin >> length;
    string = new char[length+1];
    std::cout << "введите строку ";
    std::cin.getline(string,length);
    std::cout << "введите максимальную длину слова: ";
    std::cin >> length;
    std::cout << f(string,length);
    delete[] string;
    return 0;
}