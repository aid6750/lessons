#include <iostream>

char** connect( char** matrix1,int m1,int n1, char** matrix2,int m2,int n2)
{
    //если количество столбцов отличается, операцию выполнить невозможно
    if(n1 != n2)
        return nullptr;

    char** result = new char*[m1+m2];//создан двумерный массив в котором m1+m2 строк
    for(int i = 0; i < m1+m2;i++)
        result[i] = new char[n1];


    //копируем первую матрицу в результирующую матрицу
    for(int i = 0;i<m1; i ++)
    {
        for(int j = 0;j<n1;j++)
        {
            result[i][j] = matrix1[i][j];
        }
    }
    //под первую матрицу копируем элементы из второй матрицы
    for(int i = 0;i<m2;i++)
    {
        for(int j = 0;j<n2;j++)
        {
            result[i+m1][j] = matrix2[i][j];
        }
    }
    return result;
}

int main(void)
{
    char** matrix1;
    int m1,n1;
    char** matrix2;
    int m2,n2;

    std::cout << "введите размерность первой матрицы" << std::endl;

    std::cin >> m1 >> n1;
    matrix1 = new char*[m1];
    for(int i = 0; i < m1;i++)
        matrix1[i] = new char[n1];

    for(int i = 0;i<m1;i++)
    {
        for(int j = 0;j < n1;j++)
        {
            std::cin >> matrix1[i][j];
        }
    }

    std::cout << "введите размерность второй матрицы" << std::endl;
    std::cin >> m2 >> n2;
    matrix2 = new char*[m2];
    for(int i = 0; i < m2;i++)
        matrix2[i] = new char[n2];

    for(int i = 0;i<m2;i++)
    {
        for(int j = 0;j < n2;j++)
        {
            std::cin >> matrix2[i][j];
        }
    }

    char** result = connect(matrix1,m1,n1,matrix2,m2,n2);

    if(result == nullptr)
    {
        std::cout << "невозможно выполнить операцию" << std::endl;
    }
    else
    {
        for(int i =0;i < m1+m2;i++)
        {
            for(int j = 0; j < n1;j++)
            {
                std::cout << result[i][j] << " ";
            }
            std::cout << std::endl;
        }
        delete [] result;
    }
    delete [] matrix1;
    delete [] matrix2;
    return 0;
}
