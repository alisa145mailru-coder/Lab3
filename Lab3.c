#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_natural_string(const char *str) {
    if (str[0] == '\0' || str[0] == '0' || str[0] == '-') {
        return 0;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
    }
    return 1;
}

int is_float_string(const char *str) {
    int start = 0;
    if (str[0] == '-' || str[0] == '+') {
        start += 1;
    }
    if (str[start] == '\0') {
        return 0;
    }
    int dot_count = 0;
    int digit_count = 0;
    for (int i = start; str[i] != '\0'; i++) {
        if (str[i] == '.') {
            dot_count++;
            if (dot_count > 1) {
                return 0;
            }
        } else if (str[i] >= '0' && str[i] <= '9') {
            digit_count++;
        } else {
            return 0;
        }
    }
    if (digit_count == 0) {
        return 0;
    }
    return 1;
}

int main() {
    char *N_str = NULL;
    char *M_str = NULL;
    int N, M;
    while (1) {
        printf("Введите количество строк (N >= 2): ");
        if (scanf("%ms", &N_str) != 1) {
            printf("Ошибка чтения.\n");
            free(N_str);
            continue;
        }
        if (is_natural_string(N_str)) {
            N = atoi(N_str);
            if (N < 2) {
                printf("Для задания нужно минимум 2 строки!\n");
                free(N_str);
                continue;
            }
            free(N_str);
            break;
        } else {
            free(N_str);
            printf("Число должно быть натуральным!\n");
        }
    }
    while (1) {
        printf("Введите количество столбцов (M >= 4): ");
        if (scanf("%ms", &M_str) != 1) {
            printf("Ошибка чтения.\n");
            free(M_str);
            continue;
        }
        if (is_natural_string(M_str)) {
            M = atoi(M_str);
            if (M < 4) {
                printf("Для задания нужно минимум 4 столбца!\n");
                free(M_str);
                continue;
            }
            free(M_str);
            break;
        } else {
            printf("Число должно быть натуральным!\n");
            free(M_str);
        }
    }
    float *Matrix = malloc(N * M * sizeof(float));
    if (Matrix == NULL) {
        printf("Ошибка выделения памяти!\n");
        return 1;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            char *element = NULL;
            float value;
            while (1) {
                printf("Введите элемент [%i][%i]: ", i, j);
                if (scanf("%ms", &element) != 1) {
                    printf("Ошибка чтения.\n");
                    free(element);
                    continue;
                }
                if (is_float_string(element)) {
                    value = atof(element);
                    free(element);
                    break;
                } else {
                    free(element);
                    printf("Некорректный ввод!\n");
                }
            }
            Matrix[i * M + j] = value;
        }
    }
    printf("\nИсходная матрица:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("| %f |", Matrix[i * M + j]);
        }
        printf("\n");
    }
    int max_row = 0;
    float max_val = Matrix[0 * M + 3];
    for (int i = 1; i < N; i++) {
        if (Matrix[i * M + 3] > max_val) {
            max_val = Matrix[i * M + 3];
            max_row = i;
        }
    }
    printf("\nМаксимальный элемент 4-го столбца: %f (строка %d)\n", max_val, max_row);
    double S = 10.0;
    int target_row = 1;
    for (int j = 0; j < M; j++) {
        S += exp(1.0 - Matrix[target_row * M + j]);
    }
    printf("Вычисленное значение S: %f\n", S);
    Matrix[max_row * M + 3] = (float)S;
    printf("\nМатрица после замены:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("| %f |", Matrix[i * M + j]);
        }
        printf("\n");
    }
    free(Matrix);
    return 0;
}
