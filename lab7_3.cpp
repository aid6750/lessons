#include <stdio.h>
#include <string.h>

int main()
{
    FILE* file = fopen("/home/konstantin/Desktop/text","r");

    char lines [1000][81];
    int counter = 0;
    for(int i = 0;i<1000;i++)
    {
        if(fgets(lines[i],81,file) == NULL)
        {
            break;
        }
        counter++;
    }
    fclose(file);
    file = fopen("/home/konstantin/Desktop/text","w");

    for(int i =0;i <counter;i++)
    {
        if(strlen(lines[i]) > 1)
        {
            fprintf(stdout,"%s",lines[i]);
        }
    }

    return 0;
}
 
