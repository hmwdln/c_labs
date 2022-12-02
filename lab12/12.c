#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdio_ext.h>

int mygetch()
{
    struct termios oldt, newt;
    int c;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    c = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return c;
}

typedef struct student_data 
{
    char* name;
    char* surname;
    char* full_group;
    int* exams_marks;
}sd_t;

int add_student(sd_t* element, int data_size)
{
    __fpurge(stdin);
    char* group = malloc(100);
    char* name = malloc(100);
    char* surname = malloc(100);
    int* exams_marks = malloc(3 * sizeof(int));

    printf("Фамилия: ");
    fgets(surname, 100, stdin);
    surname[strlen(surname) - 1] = '\0';
    printf("Имя: ");
    fgets(name, 100, stdin);
    name[strlen(name) - 1] = '\0';
    printf("Группа: ");
    fgets(group, 100, stdin);
    group[strlen(group) - 1] = '\0';
    printf("Оценки по трём экзаменам (через пробел): ");
    scanf("%d %d %d", &exams_marks[0], &exams_marks[1], &exams_marks[2]);

    (*element).surname = surname;
    (*element).name = name;
    (*element).full_group = group;
    (*element).exams_marks = exams_marks;
    data_size++;
    return data_size;
}

float average_value(int a[3])
{
    return (a[0] + a[1] + a[2]) / 3.0;
}

void print_student_data(sd_t element)
{
    printf("| %-19s| %-14s| %-7s| %1d %1d %1d  | %1lf",
    element.surname, element.name,
    element.full_group, element.exams_marks[0],
    element.exams_marks[1], element.exams_marks[2],
    average_value(element.exams_marks));
}

void all_student_data(sd_t data[], int data_size)
{
    printf("ID | Фамилия\t\t| Имя\t\t| Группа | Оценки | Ср. балл\n");
    for (int i = 0; i < data_size; i++)
    {
        printf("%2i ", i);
        print_student_data(data[i]);
        printf("\n");
    }
}

int remove_student(sd_t* element, int data_size)
{
    free(element->name);
    free(element->exams_marks);
    free(element->full_group);
    free(element->surname);
    return data_size - 1;
}

void excellent_marks(sd_t data[], int data_size)
{
    printf("ID | Фамилия\t\t| Имя\t\t| Группа | Оценки | Ср. балл\n");
    for (int i = 0; i < data_size; i++)
    {
        if (average_value(data[i].exams_marks) >= 4.50)
        {
            printf("%2i ", i);
            print_student_data(data[i]);
            printf("\n");
        }
    }
}

void change_student(sd_t* element)
{
    remove_student(element, 0);
    add_student(element, 0);
}

int load(sd_t data[])
{
    FILE* file = fopen("student_data.txt", "r");
    int size;
    fscanf(file, "%d\n", &size);
    for (int i = 0; i < size; i++)
    {
        char* group = malloc(100);
        char* name = malloc(100);
        char* surname = malloc(100);
        int* exams_marks = malloc(3 * sizeof(int));

        fgets(surname, 100, file);
        fgets(name, 100, file);
        fgets(group, 100, file);
        fscanf(file, "%d %d %d\n", &exams_marks[0], &exams_marks[1], &exams_marks[2]);

        surname[strlen(surname) - 1] = '\0';
        name[strlen(name) - 1] = '\0';
        group[strlen(group) - 1] = '\0';

        data[i].surname = surname;
        data[i].name = name;
        data[i].full_group = group;
        data[i].exams_marks = exams_marks;
    }
    fclose(file);
    return size;
}

void save(sd_t data[], int size)
{
    FILE* file = fopen("student_data.txt", "w");
    fprintf(file, "%d\n", size);
    for (int i = 0; i < size; i++)
    {
        fprintf(file, "%s\n%s\n%s\n%d %d %d\n",
        data[i].surname, data[i].name, data[i].full_group,
        data[i].exams_marks[0], data[i].exams_marks[1], data[i].exams_marks[2]);
    }
    fclose(file);
}

int main()
{
    sd_t data[100];
    int data_size = load(data);

    while (1)
    {
        printf("[1] - добавить студента\n[2] - вывести всех студентов\n"
        "[3] - вывести студентов, средний балл которых больше 4.5\n[4] - изменить данные студента\n"
        "[5] - удалить студента\n[q] - выход\n>");
        char key = mygetch();
        printf("\n");

        switch (key)
        {
            case '1':
                data_size = add_student(&data[data_size], data_size);
                break;
            case '2':
                all_student_data(data, data_size);
                break;
            case '3':
                excellent_marks(data, data_size);
                break;
            case '4':
                int change;
                printf("Номер изменяемого студента: ");
                scanf("%d", &change);
                if (change < data_size && change >= 0)
                    change_student(&data[change]);
                break;
            case '5':
                all_student_data(data, data_size);
                int removed;
                printf("Номер удаляемого студента: ");
                scanf("%d", &removed);
                if (removed < data_size && removed >= 0)
                {
                    data_size = remove_student(&data[removed], data_size);
                    for (int i = removed; i < data_size; i++)
                        data[i] = data[i + 1];
                }
                break;
            case 'q':
                save(data, data_size);
                return 0;
                break;
            case '\n':
                break;
            default:
                printf("Неизвестная команда\n");
                break;
        }
    }
}