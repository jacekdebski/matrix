#include "matrix_utils.h"
#include <stdlib.h>
#include <stdio.h>

void matrix_destroy(struct matrix_t *m) {
    if (m == NULL) {
        return;
    }
    if ((*m).ptr != NULL) {
        for (int i = 0; i < (*m).height; i++) {
            if (*((*m).ptr + i) != NULL) {
                free(*((*m).ptr + i));
            }
        }
        free((*m).ptr);
    }
}

int matrix_create(struct matrix_t *m, int width, int height) {
    if (m == NULL || width <= 0 || height <= 0) {
        return 1;
    }
    (*m).ptr = (int **) malloc(height * sizeof(int *));
    if ((*m).ptr == NULL) {
        matrix_destroy(m);
        return 2;
    }
    for (int i = 0; i < height; ++i) {
        *((*m).ptr + i) = (int *) malloc(width * sizeof(int));
        if (*((*m).ptr + i) == NULL) {
            for (int j = i - 1; j >= 0; j--) {
                free(*((*m).ptr + j));
                *((*m).ptr + j) = NULL;
            }
            free((*m).ptr);
            return 2;
        }
    }
    (*m).height = height;
    (*m).width = width;
    return 0;
}

int matrix_read(struct matrix_t *m) {
    if (m == NULL || (*m).ptr == NULL || (*m).width <= 0 || (*m).height <= 0) {
        return 1;
    }
    for (int i = 0; i < (*m).height; ++i) {
        if (*((*m).ptr + i) == NULL) {
            return 1;
        }
    }
    int isCorrect = 0;
    for (int i = 0; i < (*m).height; ++i) {
        for (int j = 0; j < (*m).width; ++j) {
            isCorrect = scanf("%d", *((*m).ptr + i) + j);
            if (isCorrect != 1) {
                return 2;
            }
        }
    }
    return 0;
}

void matrix_display(const struct matrix_t *m) {
    if (m == NULL || (*m).ptr == NULL || (*m).width <= 0 || (*m).height <= 0) {
        return;
    }
    for (int i = 0; i < (*m).height; ++i) {
        if (*((*m).ptr + i) == NULL) {
            return;
        }
    }
    for (int i = 0; i < (*m).height; ++i) {
        for (int j = 0; j < (*m).width; ++j) {
            printf("%d ", *(*((*m).ptr + i) + j));
        }
        printf("\n");
    }
}

struct matrix_t *matrix_create_struct(int width, int height) {
    if (width <= 0 || height <= 0) {
        return NULL;
    }
    struct matrix_t *ptr_result_matrix_t = NULL;
    ptr_result_matrix_t = (struct matrix_t *) malloc(sizeof(struct matrix_t));
    if (ptr_result_matrix_t == NULL) {
        return NULL;
    }
    (*ptr_result_matrix_t).ptr = (int **) malloc(height * sizeof(int *));
    if ((*ptr_result_matrix_t).ptr == NULL) {
        free(ptr_result_matrix_t);
        return NULL;
    }
    for (int i = 0; i < height; ++i) {
        *((*ptr_result_matrix_t).ptr + i) = (int *) malloc(width * sizeof(int));
        if (*((*ptr_result_matrix_t).ptr + i) == NULL) {
            for (int j = i - 1; j >= 0; j--) {
                free(*((*ptr_result_matrix_t).ptr + j));
            }
            free((*ptr_result_matrix_t).ptr);
            free(ptr_result_matrix_t);
            return NULL;
        }
    }
    (*ptr_result_matrix_t).width = width;
    (*ptr_result_matrix_t).height = height;
    return ptr_result_matrix_t;
}

void matrix_destroy_struct(struct matrix_t **m) {
    if (m == NULL || *m == NULL) {
        return;
    }
    if ((**m).ptr != NULL) {
        for (int i = 0; i < (**m).height; i++) {
            if (*((**m).ptr + i) != NULL) {
                free(*((**m).ptr + i));
                *((**m).ptr + i) = NULL;
            }
        }
        free((**m).ptr);
    }
    free(*m);
    *m = NULL;
}

struct matrix_t *matrix_transpose(const struct matrix_t *m) {
    if (m == NULL || (*m).ptr == NULL || (*m).width <= 0 || (*m).height <= 0) {
        return NULL;
    }
    for (int i = 0; i < (*m).height; ++i) {
        if (*((*m).ptr + i) == NULL) {
            return NULL;
        }
    }
    struct matrix_t *ptr_result_matrix_t = matrix_create_struct((*m).height, (*m).width);
    if (ptr_result_matrix_t == NULL) {
        return NULL;
    }
    for (int i = 0; i < (*ptr_result_matrix_t).height; ++i) {
        for (int j = 0; j < (*ptr_result_matrix_t).width; ++j) {
            *(*((*ptr_result_matrix_t).ptr + i) + j) = *(*((*m).ptr + j) + i);
        }
    }
    return ptr_result_matrix_t;
}

int matrix_save_b(const struct matrix_t *m, const char *filename) {
    if (m == NULL || (*m).ptr == NULL || (*m).width <= 0 || (*m).height <= 0 || filename == NULL) {
        return 1;
    }
    for (int i = 0; i < (*m).height; ++i) {
        if (*((*m).ptr + i) == NULL) {
            return 1;
        }
    }
    FILE *ptrFile = NULL;
    ptrFile = fopen(filename, "wb");
    if (ptrFile == NULL) {
        return 2;
    }
    int iResultWrite = 0;
    iResultWrite = fwrite(&((*m).width), sizeof(int), 1, ptrFile);
    if (iResultWrite != 1) {
        fclose(ptrFile);
        return 3;
    }
    iResultWrite = fwrite(&((*m).height), sizeof(int), 1, ptrFile);
    if (iResultWrite != 1) {
        fclose(ptrFile);
        return 3;
    }
    for (int i = 0; i < (*m).height; ++i) {
        iResultWrite = fwrite(*((*m).ptr + i), sizeof(int), (*m).width, ptrFile);
        if (iResultWrite != (*m).width) {
            fclose(ptrFile);
            return 3;
        }
    }
    fclose(ptrFile);
    return 0;
}

int matrix_save_t(const struct matrix_t *m, const char *filename) {
    if (m == NULL || (*m).ptr == NULL || (*m).width <= 0 || (*m).height <= 0 || filename == NULL) {
        return 1;
    }
    for (int i = 0; i < (*m).height; ++i) {
        if (*((*m).ptr + i) == NULL) {
            return 1;
        }
    }
    FILE *ptrFile = NULL;
    ptrFile = fopen(filename, "w");
    if (ptrFile == NULL) {
        return 2;
    }
    int iResultWrite = 0;
    iResultWrite = fprintf(ptrFile, "%d %d\n", (*m).width, (*m).height);
    if (iResultWrite == 0) {
        fclose(ptrFile);
        return 3;
    }
    for (int i = 0; i < (*m).height; ++i) {
        for (int j = 0; j < (*m).width; ++j) {
            iResultWrite = fprintf(ptrFile, "%d ", *(*((*m).ptr + i) + j));
            if (iResultWrite == 0) {
                fclose(ptrFile);
                return 3;
            }
        }
        iResultWrite = fprintf(ptrFile, "\n");
        if (iResultWrite != 1) {
            fclose(ptrFile);
            return 3;
        }
    }
    fclose(ptrFile);
    return 0;
}
