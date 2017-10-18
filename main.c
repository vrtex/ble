#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#define NEW_LINE_SYMBOL '\n'
typedef struct matrix matrix;

struct matrix
{
    int rows, cols;
    float *table;
};

int countNewLines(FILE *f)
{
    int checkpoint = ftell(f);
    int lines = 0;
    char c;
    do {
        c = fgetc(f);
        if(c == NEW_LINE_SYMBOL)
        ++lines;
    } while(c == ' ' || c == '\t' || c == NEW_LINE_SYMBOL);
    fseek(f, checkpoint, 0);
    return lines;
}

void initMatrix(matrix *ptr, int x)
{
    int i;
    ptr->rows = ptr->cols = x;
    ptr->table = (float *)malloc(x * x * (int)sizeof(float));
    for(i = 0; i < x * x; ++i)
        *(ptr->table + i) = 0.0f;
}

bool loadMatrix(matrix *ptr, char *path)
{
    FILE *f = fopen(path, "r");
    if(!f) return false;
    initMatrix(ptr, 0);
    if(countNewLines(f) != 0)
    {
        fclose(f);
        return false;
    }

    if(fscanf(f, "%d", &ptr->rows) != 1 || ptr->rows <= 0)
    {
        fclose(f);
        return false;
    }
    if(countNewLines(f) != 1)
    {
        fclose(f);
        return false;
    }
    initMatrix(ptr, ptr->rows);
    int x = 0, y = 0, expectedLines = 0;
    float a = 0;
    for(y = 0; y < ptr->rows; ++y)
    {
        for(x = 0; x < ptr->cols; ++x)
        {
            if(x == ptr->cols - 1) expectedLines = 1;
            else expectedLines = 0;
            if(fscanf(f, "%f", &a) != 1 || countNewLines(f) != expectedLines)
            {
                fclose(f);
                return false;
            }
            *(ptr->table + x + y * ptr->cols) = a;
        }
    }
    /*
    for(i = 0; i < ptr->cols * ptr->rows; ++i)
    {
        if(fscanf(f, "%f", &j) != 1)
        {
            fclose(f);
            return false;
        }
        *(ptr->table + i) = j;
    }
    */
    if(fscanf(f, "%f", &a) != EOF)
    {
        printf("wrond number of numbers\n");
        fclose(f);
        return false;
    }
    fclose(f);
    return true;
}

void showMatrix(matrix *ptr)
{
    printf("-----------------\n\n");
    int i, j;
    for(i = 0; i < ptr->rows; ++i)
    {
        for(j = 0; j < ptr->cols; ++j)
        {
            printf("%.2f ", *(ptr->table + i * ptr->cols + j));
        }
        printf("\n");
    }
    printf("-----------------\n\n");
}

void fillMatrix(matrix *ptr)
{
    int i, j;
    for(i = 0; i < ptr->rows; ++i)
    {
        for(j = 0; j < ptr->cols; ++j)
        {
            //*(ptr->table + i * ptr->cols + j) = (float)rand() / RAND_MAX * 30;
            printf("Enter element [%d, %d]: ", i, j);
            scanf("%f", (ptr->table + i * ptr->cols + j));
            fflush(stdin);
        }
    }
}

void freeMatrix(matrix *ptr)
{
    if(ptr->table == NULL) return;
    free(ptr->table);
    ptr->cols = 0;
    ptr->rows = 0;
}

void fillMinor(matrix *ptr, matrix *minor, int ignoreCol)
{
    int x, y, offset = 0;
    for(x = 0; x < minor->cols; ++x)
    {
        if(x == ignoreCol) offset = 1;
        for(y = 0; y < minor->rows; ++y)
        {
            *(minor->table + y * minor->cols + x) = *(ptr->table + y * ptr->cols + x + offset);
        }
    }
}

float determinant(matrix *ptr)
{
    if(ptr->cols == 1)
    {
        return *(ptr->table);
    }
    matrix minor;
    initMatrix(&minor, ptr->cols - 1);
    float w = 0;
    int factor, i;
    if(ptr->rows % 2) factor = 1;
    else factor = -1;
    for(i = 0; i < ptr->cols; ++i)
    {
        fillMinor(ptr, &minor, i);
        w += factor * determinant(&minor) * *(ptr->table + ptr->cols * (ptr->rows - 1) + i);
        factor *= -1;
    }
    freeMatrix(&minor);
    return w;
}

int main()
{
    srand(time(0));
    matrix m1;
    if(loadMatrix(&m1, "mat.txt")) printf("hello\n");
    else
    {
        printf("goodbye\n");
        freeMatrix(&m1);
        abort();
    }
    showMatrix(&m1);
    printf("det: %f\n", determinant(&m1));
	freeMatrix(&m1);
    return 0;
}
