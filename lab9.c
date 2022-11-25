#include <stdio.h>
#include <string.h>

int find_len_without_repeats(int i, int len, char str[])
{
    char a[256] = {0,};
    for (int j = i; j < len; j++)
    {
        if (a[(int)str[j]] != 0)
        {
            return j - i;
        }

        else
        {
            a[(int)str[j]] = 1;
        }
    }
    return len - i;
}

int main()
{
    char str[256];
    scanf("%[^\n]", str);
    int len = strlen(str);
    int max_len = 0;
    int current_len;
    int max_start;
    for (int i = 0; i < len; i++)
    {
        current_len = find_len_without_repeats(i, len, str);
        if (current_len > max_len)
        {
            max_len = current_len;
            max_start = i;
        }
    }
    char substr[256];
    strncpy(substr, str + max_start, max_len);
    substr[max_len] = '\0';
    printf("%s\n", substr);
}
