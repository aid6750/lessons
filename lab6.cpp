#include <iostream>
#include <algorithm>
const double min_wage = 1000; // минимальная заработная плата
//переменная создана в глобальной области видимости, чтоб не было необходимости передавать ее в функции

//структура студент
struct student
{
    char name[256];//имя студента может содержать не более 255 символов
    char group[32];
    double score;
    double income;
};


void swap(student& s1,student& s2)
{
    student t = s1;
    s1 = s2;
    s2 = t;
}


bool compare(const student& s1, const student& s2)
{
    // если у обоих студентов доход меньше минимума, то выше в рейтинге тот, у которого доход меньше
    if(s1.income < min_wage*2 and s2.income < min_wage*2)
        return s1.income < s2.income;

    //если у одного из студентов доход меньше минимума, а у другого больше, то выше в рейтинге тот,
    //у которого доход меньше
    if(s1.income < min_wage*2 and s2.income >= min_wage*2)
        return true;
    
    if(s1.income >= min_wage*2 and s2.income < min_wage*2)
        return false;

    //если у обоих студентов доход больше минимума, то выше в рейтинге тот, у которого больше средний балл
    return s1.score > s2.score;

}


void sort(student s[],uint64_t N)
{
    for(int i = 0;i < N;i++)
    {
        for(int j = 0; j< N-1;j++)
        {
            if(compare(s[j+1],s[j]))
                swap(s[j+1],s[j]);
        }
    }    
}


int main(void)
{

    student students[4];


    std::cout << "сколько студентов? " << std::endl;
    uint64_t N;
    std::cin >> N;
    for (int i = 0; i < N;i++)
    {
        std::cout << "введите данные студента" << std::endl;
        std::cout << "введите номер группы: ";
        std::cin >> students[i].group;
        std::cout << "введите доход на члена семьи: ";
        std::cin >> students[i].income;
        std::cout << "введите средний балл: ";
        std::cin >> students[i].score;
        std::cout << "введите имя: ";
        std::cin >> students[i].name;
    }

    sort(students,N);


    for(int i = 0;i < 4;i++)
    {
        std::cout << "имя= " << students[i].name << std::endl;
        std::cout << "Номер группы: " << students[i].group << std::endl;
        std::cout << "средний балл " << students[i].score << std::endl;
        std::cout << "доход на члена семьи " << students[i].income << std::endl; 
        std::cout << "----------------------------------------------------------";
        std::cout << "----------------------------------------------------------";
    }

    return 0;
}