#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row;
    int col;
    int value;
} element;

typedef struct SparseMatrix {
    element* data;
    int rows;
    int cols;
    int terms;
} SparseMatrix;

SparseMatrix matrix_transpose(SparseMatrix a)
{
    SparseMatrix b;
    int bindex;
    b.rows = a.cols;
    b.cols = a.rows;
    b.terms = a.terms;

    if (a.terms > 0) {
        b.data = (element*)malloc(b.terms * sizeof(element));
        if (b.data == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            exit(1);
        }

        bindex = 0;
        for (int c = 0; c < a.cols; c++) {
            for (int i = 0; i < a.terms; i++) {
                if (a.data[i].col == c) {
                    b.data[bindex].row = a.data[i].col;
                    b.data[bindex].col = a.data[i].row;
                    b.data[bindex].value = a.data[i].value;
                    bindex++;
                }
            }
        }
    }
    else {
        b.data = NULL;
    }
    return b;
}

SparseMatrix get_input_sparse_matrix() {
    SparseMatrix m;
    printf("Enter the size of rows and colums, the number of non-zero terms: ");
    scanf_s("%d %d %d", &m.rows, &m.cols, &m.terms);

    m.data = (element*)malloc(m.terms * sizeof(element));
    if (m.data == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }

    printf("Enter row, column, and value pairs in order:\n");
    for (int i = 0; i < m.terms; i++) {
        scanf_s("%d %d %d", &m.data[i].row, &m.data[i].col, &m.data[i].value);
    }
    return m;
}

void matrix_print(SparseMatrix a)
{
    printf("====================\n");
    for (int i = 0; i < a.terms; i++) {
        printf("(%d, %d, %d) \n", a.data[i].row, a.data[i].col, a.data[i].value);
    }
    printf("====================\n");
}

int main(void)
{
    SparseMatrix m = get_input_sparse_matrix();
    SparseMatrix result = matrix_transpose(m);
    printf("Transposed matrix:\n");
    matrix_print(result);

    free(m.data);
    free(result.data);
    return 0;
}