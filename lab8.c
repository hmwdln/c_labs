#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio_ext.h>

int mygetch()
{
    struct termios oldt, newt;
    int c;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    c = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return c;
}

enum reading
{
    before_entering,
    first,
    second,
    first_symbol_second,
    first_symbol_exponent,
    exponent,
    control
};

int main()
{
    char sym_valid = 1;
    char count = 0;
    char ctrl_1;
    char ctrl_2;
    enum reading mode = before_entering;
    enum reading old_mode;

    while(1)  
    {   
        char a = mygetch();
        
        if (a == 0x1b)
        {
            count = 0;
            old_mode = mode;
            mode = control;
            continue;
        }
        
        if (isprint(a) && mode != control)
        {
            printf("%c", a);
        }
        
        if (mode == control)
        {
            if (count == 0)
            {
                ctrl_1 = a;
            }
            
            else
            {
                ctrl_2 = a;
                __fpurge(stdin);
                mode = old_mode;
                if (ctrl_1 == 0x5b)
                    if (ctrl_2 == 0x46)
                        break;
                continue;
            }
            count++;
        }
        
        if (!(isdigit(a) || a == '-' || a == '.' || a == 'e' || a == '+') && mode != control)
            sym_valid = 0;
        
        if (mode == before_entering)
        {
            if (!(isdigit(a) || a == '-' || a == '+'))
            {
                sym_valid = 0;
            }

            else
            {
                mode = first;
                continue;
            }
        }

        if (mode == first)
        {
            if(!(isdigit(a) || a == '.' || a == 'e' || a == '+'))
            {
                sym_valid = 0;
            }

            if (a == '.')
            {
                mode = first_symbol_second;
                continue;
            }

            if (a == 'e')
            {
                mode = first_symbol_exponent;
                continue;
            }
        }

        if (mode == first_symbol_second)
        {
            if (!(isdigit(a)))
            {
                sym_valid = 0;
            }
            
            mode = second;
            continue;
        }

        if (mode == second)
        {
            if (!(isdigit(a) || a == 'e'))
            {
                sym_valid = 0;
            }

            if (a == 'e')
            {
                mode = first_symbol_exponent;
                continue;
            }
        }

        if (mode == first_symbol_exponent)
        {
            if(!(isdigit(a) || a == '-' || a == '+'))
            {
                sym_valid = 0;
            }

            mode = exponent;
            continue;
        }

        if (mode == exponent)
        {
            if (!(isdigit(a)))
            {
                sym_valid = 0;
            }
        }


    }   

    if (mode != before_entering && (sym_valid == 1) && count != 0)
    {
        printf("\nПоследовательность является вещественным числом\n");
    }
    else
    {
        printf("\nПоследовательность не является вещественным числом\n");
    }

    return 0;
}