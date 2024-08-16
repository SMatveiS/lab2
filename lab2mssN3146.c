#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

void redmat(int *mas[], int cols, int rows);
void checkint(char *ch);
int main(int argc, char *argv[]) {
    if (argc > 4 || argc < 3)
    	fprintf(stderr, "Usage: %s [-m] число_строк число_столбцов\n", argv[0]);

    else if (argc == 3) {          // отсутствует -m
    	checkint(argv[1]);         // Проверка на то, что передаваемые аргументы - числа
    	checkint(argv[2]);
    	
    	int n = atoi(argv[1]);     // Преобразование аргументов в формат int
        int m = atoi(argv[2]);
        int arr[n][m];
        for (int i = 0; i < n; ++i) {              // Создание массива, заполненного случайными значениями до 1000
            for (int j = 0; j < m; ++j)
                arr[i][j] = rand() % 1000;
        }
        
        for (int i = 0; i < n; ++i) {          // Выводим полученную матрицу на экран
            for (int j = 0; j < m; ++j)
                printf("%d ", arr[i][j]);
            printf("\n");
        }
        
        int *mas[n];                       // Создаём массив из указателей на строки матрицы
        for (int i = 0; i < n; ++i)
            mas[i] = arr[i];
        
        redmat(mas, n, m);                 // Передаём этот массив в функцию
    }
    
    
    else {
    	if (strcmp(argv[1], "-m")) {       // Проверка аргумента -m
            fprintf(stderr, "Usage: %s [-m] число_строк число_столбцов\n", argv[0]);
            return EXIT_FAILURE;
        }
        checkint(argv[2]);            // Проверка на то, что передаваемые аргументы - числа
        checkint(argv[3]);
        
        int n = atoi(argv[2]);        // Преобразование аргументов в формат int
        int m = atoi(argv[3]);
        int arr[n][m];
        int num;
        printf("Введите матрицу размера %d на %d\n", n, m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                while (scanf("%d", &num) != 1) {
                    printf("Введите целое число\n");
                    char ch;
                    while (!isspace(ch = getchar()))       // Откидываем лишние символы
                        ;
                }
                arr[i][j] = num;
            }
        }
        for (int i = 0; i < n; ++i) {           // Выводим полученную матрицу на экран
            for (int j = 0; j < m; ++j)
                printf("%d ", arr[i][j]);
            printf("\n");
        }
        
        int *mas[n];                     // Создаём массив из указателей на строки матрицы
        for (int i = 0; i < n; ++i)
            mas[i] = arr[i];
        
        redmat(mas, n, m);         // Передаём этот массив в функцию
    }
    return EXIT_SUCCESS;
}


void checkint(char *ch) {
    int len = strlen(ch);
    for (int i = 0; i <= len-1; ++i) {  // (len-1) чтобы не учитывался последний непечатаемый символ, который учитывается операцией strlen
        if ((ch[i] > 57) || (ch[i] < 48)) { // Проверяем, что каждый символ цифра (втаблице ASCII цифры между 48 и 57 номером)
    	    printf("Ошибка: \'%s\' не является целым неотрицательным числом.\n", ch);
    	    exit(0);
	}
    }
}

void redmat(int *mas[],int rows, int cols) {
    int mas_sum[cols];           // Создаём массив, в которой будут храниться характеристики столбцов матрицы,  и его копию
    int mas_sum1[cols];
    for (int i = 0; i < cols; ++i) {
        mas_sum[i] = 0;          // Заполняем массивы нулями
        mas_sum1[i] = 0;
    }
    for (int i = 0; i < cols; ++i) {         // Считаем характеристики столбцов матрицы и записываем в массивы
        for (int j = 0; j < rows; j += 2) {
	    mas_sum[i] += *(mas[j] + i);
	    mas_sum1[i] += *(mas[j] + i);
	}
    }
    
    for (int i = cols - 1; i > 0; --i) {         // Сортируем один из массивов
        for (int j = 0; j < i; ++j) {
            int temp;
            if (mas_sum[j] < mas_sum[i]) {
                temp = mas_sum[i];
                mas_sum[i] = mas_sum[j];
                mas_sum[j] = temp;
            }
        }
    }
   
    int mas_flags[cols];                // Создаём массив флагов, чтобы знать какие столбцы матрицы уже были выведены
    for (int i = 0; i < cols; ++i)      // Чтобы избежать повторений
        mas_flags[i] = 1;
    
    int new_mas[rows][cols];            // Создаём массив для изменённой матрицы и заполняем значениями согласно заданию
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (mas_sum[i] == mas_sum1[j]) {
                if (mas_flags[j]) {         // Если флаг равен нулю, то этот столбец уже использован
                    mas_flags[j] = 0;     
                    for (int k = 0; k < rows; ++k)
                        new_mas[k][i] = *(mas[k] + j);
                    break;
                }
            }
        }
    }
    
    printf("\n\n");
    for (int i = 0; i < rows; ++i) {        // Выводим новую матрицу на экран
        for (int j = 0; j < cols; ++j)
            printf("%d ", new_mas[i][j]);
        printf("\n");
    }
}
