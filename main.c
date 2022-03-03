#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix_utils.h"

int main() {
    int iUser_width = 0;
    int iUser_height = 0;
    int isCorrect = 0;
    printf("Input width and height: ");
    isCorrect = scanf("%d %d", &iUser_width, &iUser_height);
    if (isCorrect != 2) {
        printf("Incorrect input");
        return 1;
    }
    if (iUser_height <= 0 || iUser_width <= 0) {
        printf("Incorrect input data");
        return 2;
    }
    struct matrix_t *ptr_user_matrix_t = matrix_create_struct(iUser_width, iUser_height);
    if (ptr_user_matrix_t == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj wartości: ");
    int iResult_matrix_read = 0;
    iResult_matrix_read = matrix_read(ptr_user_matrix_t);
    if (iResult_matrix_read == 2) {
        printf("Incorrect input");
        matrix_destroy_struct(&ptr_user_matrix_t);
        return 1;
    }
    char *filename = NULL;
    filename = (char *) calloc(40, sizeof(char));
    if (filename == NULL) {
        printf("Failed to allocate memory");
        matrix_destroy_struct(&ptr_user_matrix_t);
        return 8;
    }
    printf("Podaj sciezke do pliku \n");
    scanf("%39s", filename);
    char *ptr_dot = NULL;
    ptr_dot = strrchr(filename, '.');
    if (ptr_dot == NULL) {
        printf("Unsupported file format");
        free(filename);
        matrix_destroy_struct(&ptr_user_matrix_t);
        return 7;
    }
    struct matrix_t *ptr_user_matrix_t_transposed = matrix_transpose(ptr_user_matrix_t);
    if (ptr_user_matrix_t_transposed == NULL) {
        printf("Failed to allocate memory");
        free(filename);
        matrix_destroy_struct(&ptr_user_matrix_t);
        return 8;
    }
    matrix_destroy_struct(&ptr_user_matrix_t);
    int iResult_matrix_save = 0;
    if (strcmp(ptr_dot, ".bin") == 0) {
        iResult_matrix_save = matrix_save_b(ptr_user_matrix_t_transposed, filename);
        if (iResult_matrix_save == 2) {
            printf("Couldn't create file");
            free(filename);
            matrix_destroy_struct(&ptr_user_matrix_t_transposed);
            return 5;
        }
    } else if (strcmp(ptr_dot, ".txt") == 0) {
        iResult_matrix_save = matrix_save_t(ptr_user_matrix_t_transposed, filename);
        if (iResult_matrix_save == 2) {
            printf("Couldn't create file");
            free(filename);
            matrix_destroy_struct(&ptr_user_matrix_t_transposed);
            return 5;
        }
    } else {
        printf("Unsupported file format");
        free(filename);
        matrix_destroy_struct(&ptr_user_matrix_t_transposed);
        return 7;
    }
    printf("File saved");
    matrix_destroy_struct(&ptr_user_matrix_t_transposed);
    free(filename);
    return 0;
}
