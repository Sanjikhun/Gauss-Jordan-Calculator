#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
void identity(float mat[100][100],float num[],float idty[100][100], int i, int r,int c);
void display(float mat[100][100],float num[],float idty[100][100], int r, int c);
void first_operation(float mat[100][100],float num[],float idty[100][100],int r,int c, int i, int j);
void second_operation(float mat[100][100],float num[], float idty[100][100],int r,int c, int i, int j);
void checker(float mat[100][100],float num[],float idty[100][100],int i, int r,int c);
int scanner(float mat[100][100],float num[], int c, int i, int j, int n);
int main(int argc, char const *argv[])
{
    start: printf("\nGAUSS-JORDAN CALCULATOR\n\n");
    float matrix[100][100],cons[100],id[100][100];
    int i,j,row,column,pivot,target,pass,counter=0;
    char choice;
    printf("Number of Rows: ");
    scanf("%i",&row);
    printf("Number of Columns: ");
    scanf("%i",&column);
    if(column<=0 || row<=0)
    {
        printf("Invalid Matrix!!!");
        goto trial;
    }
    printf("Enter the Coefficient Matrix\n");
    for(i=0;i<row;++i)
    {
        for(j=0;j<column;++j)
        {
            scanf("%f",&matrix[i][j]);
        }
    }
    printf("\n\nInput the Constant Matrix\n");
    for(i=0;i<row;i++)
    {
        scanf("%f",&cons[i]);
    }
    printf("\n\nEnter the Identity Matrix\n");
    for(i=0;i<row;++i)
    {
        for(j=0;j<column;++j)
        {
            scanf("%f",&id[i][j]);
        }
    }
    printf("Matrix Input:\n");
    display(matrix,cons,id,row,column);
    for(pivot = 0;pivot<row;pivot++)
    {
        target = pivot+1;
        printf("\nFormula: R%i = R%i/%.3f",pivot+1,pivot+1,matrix[pivot][pivot]);
        printf("\n\nRow %i Operations:\n",pivot+1);
        identity(matrix,cons,id,pivot,row,column);
        display(matrix,cons,id,row,column);
        for(i = target; i<row; i++)
        {
            if(matrix[target][pivot]>0)
            {
                printf("\nFormula: R%i = -%.3fR%i + R%i",target+1,matrix[target][pivot],pivot+1,target+1);
            }
            else
            {
                printf("\nFormula: R%i = %.3fR%i - R%i",target+1,matrix[target][pivot],pivot+1,target+1);
            }
            first_operation(matrix,cons,id,row,column,target,pivot);
            printf("\n\nRow %i Operations:\n",i+1);
            display(matrix,cons,id,row,column);
            counter = scanner(matrix,cons,column,target,pivot,counter);
            if(counter==column)
            {
                printf("\n\n=======NO SOLUTION!!!=======\n");
                goto trial;
            }
            else if(counter>column)
            {
                printf("\n\n=======INFINITE SOLUTION!!!=======\n");
                goto trial;
            }
            target++;
            counter = 0;
        }
        for(pass = 0; pass<pivot; pass++)
        {
            printf("\nFormula: R%i = -%.3fR%i + %i",pass+1,matrix[pass][pivot],pivot+1,target+1);
            second_operation(matrix,cons,id,row,column,pass,pivot);
            printf("\n\nRow %i Operations:\n",pass+1);
            display(matrix,cons,id,row,column);
            counter = scanner(matrix,cons,column,pass,pivot,counter);
            if(counter==column)
            {
                printf("\n\n=======NO SOLUTION!!!=======\n");
                goto trial;
            }
            else if(counter>column)
            {
                printf("=======INFINITE SOLUTION!!!=======\n");
                goto trial;
            }
            counter = 0;
        }
    }
    for(i=0;i<row;i++)
    {
        checker(matrix,cons,id,i,row,column);
    }
    printf("\n\nFinal Operation:\n");
    display(matrix,cons,id,row,column);
    printf("==============================");
    printf("\n\nInverse Matrix\n");
    for(i=0;i<column;i++)
    {
        for(j=0;j<column;j++)
        {
            printf("%f\t",id[i][j]);
            if(j==column-1)
            {
                printf("\n");
            }
        }
    }
    printf("\n\nVariable Value:\n");
    for(i=0;i<column;i++)
    {
        printf("x%i = %f\n",i+1,cons[i]);
    }
    printf("\n\n==============================\n");
    trial: printf("Do you want to TRY AGAIN?(Y)/(N): ");
    scanf(" %c",&choice);
    if(choice=='Y' || choice=='y')
    {
        system("cls");
        goto start;
    }
    else if(choice=='N'||choice=='n')
    {
        return 0;
    }
    else
    {
        printf("Invalid Input!!!");
        goto trial;
    }
    return 0;
}
void identity(float mat[100][100],float num[],float idty[100][100], int i, int r,int c)
{
    int j,k;
    for(j=0;j<c;j++)
    {
        if(i==j)
        {
            float n = mat[i][j];
            for(j=0;j<c;j++)
            {
               mat[i][j]/=n;
            }
            for(k=0;k<c;k++)
            {
               idty[i][k]/=n;
            }
            num[i] /= n;
        }
    }
}
void display(float mat[100][100],float num[],float idty[100][100], int r, int c)
{
    int i,j,k;
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            printf("%.3f\t",mat[i][j]);
        }
        for(k=0;k<c;k++)
        {
            printf("%.3f\t",idty[i][k]);
        }
        printf("|%.3f\n",num[i]);
    }
}
void first_operation(float mat[100][100],float num[],float idty[100][100],int r,int c, int i, int j)
{
    int val;
    float var = mat[i][j];
    if(mat[i][j]!=0)
    {
        if(mat[i][j] > 0)
        {
            for(val = 0; val<c; val++)
            {
                mat[i][val] = (-var*mat[j][val]) + mat[i][val];
            }
           for(val=0;val<c;val++)
            {
                idty[i][val] = (-var*idty[j][val]) + idty[i][val];
            }
            num[i] = -var*num[j] + num[i];
        }
        else if(mat[i][j] < 0)
        {
            for(val = 0; val<c; val++)
            {
                mat[i][val] = (var*mat[j][val]) - mat[i][val];
            }
            for(val=0;val<c;val++)
            {
                idty[i][val] = (var*idty[j][val]) - idty[i][val];
            }
            num[i] = var*num[j] - num[i];
        }
    }
}
void second_operation(float mat[100][100],float num[], float idty[100][100],int r,int c, int i, int j)
{
    int val;
    float var = mat[i][j];
    if(mat[i][j]!=0)
    {
        for(val = 0; val<c; val++)
        {
            mat[i][val] = (-var*mat[j][val]) + mat[i][val] ;
        }
        for(val=0;val<c;val++)
        {
            idty[i][val] = (-var*idty[j][val]) + idty[i][val] ;
        }
        num[i] = -var*num[j] + num[i];
    }
}
int scanner(float mat[100][100],float num[], int c, int i, int j,int n)
{
    int val;
    for(val = 0; val<c; val++)
    {
        if(mat[i][val]==0)
        {
            n++;
        }
    }
    if(num[i]==0 && n==c)
    {
        n++;
    }
    return(n);
}
void checker(float mat[100][100],float num[],float idty[100][100],int i, int r,int c)
{
    int j;
    for(j=0;j<c;j++)
    {
        if(i==j && mat[i][j] != 1)
        {
            float n = mat[i][j];
           for(j=0;j<c;j++)
           {
               mat[i][j]/=n;
           }
           for(j=0;j<c;j++)
           {
               idty[i][j]/=n;
           }
           num[i] /= n;
        }
        else if(i!=j && mat[i][j]==0)
        {
            mat[i][j] = 0;
        }
    }
}
