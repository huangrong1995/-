#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int Cmp(const void* a, const void* b)
{
    int* ap = *(int**)a;
    int* bp = *(int**)b;

    if (ap[0] == bp[0])
        return ap[1] - bp[1];
    else
        return ap[0] - bp[0];
}

int Max(int a, int b)
{
    return a > b ? a : b;
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int* returnColumnSizes)
{
    if (intervals == NULL) {
        *returnSize = 0;
        return intervals;
    }
    qsort(intervals, intervalsSize, sizeof(intervals[0]), Cmp);

    int j;
    for (j = 0; j < intervalsSize; j++) {
        printf("Sort:j = %d, {%d, %d}\n", j, intervals[j][0], intervals[j][1]);
    }
    printf("------------------------------------------------\n");

    int** res = (int**)malloc(sizeof(int*) * intervalsSize);
    returnColumnSizes = (int*)malloc(intervalsSize * sizeof(int));
    int i;
    *returnSize = 0;
    for (i = 0; i < intervalsSize; i++) {
        if (i == intervalsSize - 1) {
            res[*returnSize] = (int*)malloc(sizeof(int) * 2);
            returnColumnSizes[*returnSize] = 2;
            memcpy(res[*returnSize], intervals[i], sizeof(intervals[i]));
            (*returnSize)++;
            break;
        }
        if (intervals[i][1] >= intervals[i + 1][0]) {
            intervals[i + 1][0] = intervals[i][0];
            intervals[i + 1][1] = Max(intervals[i][1], intervals[i + 1][1]);
        }
        else {
            res[*returnSize] = (int*)malloc(sizeof(int) * 2);
            returnColumnSizes[*returnSize] = 2;
            memcpy(res[*returnSize], intervals[i], sizeof(intervals[i]));
            (*returnSize)++;
        }
    }
    return res;
}

int main()
{
    int i;
    int intervals[][2] = { {0, 2}, {3, 5}, {4, 6}, {7, 9} };
    int intervalsSize = 4;
    int intervalsColSize;
    int returnSize;
    int* returnColumnSizes = NULL;
    int** obj = NULL, ** res = NULL;
    obj = (int**)malloc(sizeof(int*) * intervalsSize);
    for (i = 0; i < intervalsSize; i++) {
        obj[i] = (int*)malloc(sizeof(int) * 2);
        memcpy(obj[i], intervals[rand() % 4], 2 * sizeof(int));
        printf("Copy:i = %d, {%d, %d}\n", i, obj[i][0], obj[i][1]);
    }
    printf("------------------------------------------------\n");

    res = merge(obj, intervalsSize, &intervalsColSize, &returnSize, returnColumnSizes);
    for (i = 0; i < returnSize; i++) {
        printf("Result:i = %d, {%d, %d}\n", i, res[i][0], res[i][1]);
    }
    printf("------------------------------------------------\n");
    return 0;
}
