#include<stdio.h>

void get_matrix(int row,int col,int mat[row][col]);
void print_mat(int row,int col,int mat[row][col]);
void add_matrix(int row, int col, int mat1[row][col], int mat2[row][col], int add_res[row][col]);
void sub_matrix(int row, int col, int mat1[row][col], int mat2[row][col], int sub_res[row][col]);
void mul_matrix(int row1, int col1, int row2, int col2, int mat1[row1][col1], int mat2[row2][col2], int mul_res[row1][col2]);

int main()
{
    int row1, col1, row2, col2;
    printf("Day - 21 - Matrix Operations\n");

    printf("row1: ");
    scanf("%d",&row1);

    printf("\ncol1: ");
    scanf("%d",&col1);

    printf("row2: ");
    scanf("%d",&row2);

    printf("\ncol2: ");
    scanf("%d",&col2);

    int mat1[row1][col1];
    int mat2[row2][col2];

    int add_res[row1][col1]; // for adding both the row1 and row2, and col1 and col2 has to be the same
    int sub_res[row1][col1];
    int mul_res[row1][col2];

    printf("matrix 1:\n");
    get_matrix(row1, col1, mat1);
    printf("matrix 2:\n");
    get_matrix(row2, col2, mat2);

    printf("matrix 1: \n");
    print_mat(row1, col1, mat1);

    printf("matrix 2: \n");
    print_mat(row2, col2, mat2);

    if(row1 != row2 || col1 != col2)
    {
        printf("Can't add or subtract\n");
    }
    else
    {
        add_matrix(row1, col1, mat1, mat2, add_res);
        
        printf("matrix addition result: \n");
        print_mat(row1, col1, add_res); // dimensions of either of the array

        sub_matrix(row1, col1, mat1, mat2, sub_res);
        
        printf("matrix subtraction result: \n");
        print_mat(row1, col1, sub_res);
    }

    if(col1 != row2)
    {
        printf("Can't multiply\n");
    }
    else
    {
        mul_matrix(row1, col1, row2, col2, mat1, mat2, mul_res);

        printf("matrix multiplication result: \n");
        print_mat(row1, col2, mul_res);
    }

}

void get_matrix(int row,int col,int mat[row][col])
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            printf("row %d, col %d\n", i, j);
            scanf("%d",&mat[i][j]);
        }
    }
}

void print_mat(int row,int col,int mat[row][col])
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
}

void add_matrix(int row, int col, int mat1[row][col], int mat2[row][col], int add_res[row][col])
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            add_res[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}

void sub_matrix(int row, int col, int mat1[row][col], int mat2[row][col], int sub_res[row][col])
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            sub_res[i][j] = mat1[i][j] - mat2[i][j];
        }
    }
}

void mul_matrix(int row1, int col1, int row2, int col2, int mat1[row1][col1], int mat2[row2][col2], int mul_res[row1][col2])
{
    for(int i = 0; i < row1; i++)
    {
        for(int j = 0; j < col2; j++)
        {
            int sum = 0;
            for(int k = 0; k < col1; k++) // limit can be col1 or row2
            {
                sum += mat1[i][k] * mat2[k][j];
            }
            mul_res[i][j] = sum;
            //add_res[i][j] = mat1[i][j] - mat2[i][j];
        }
    }
}