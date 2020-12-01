//PROGRAM FOR MATRIX MULTIPLICATION 

#include <stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct ARG
{
   int i,j,k;
   int M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,r1; 
   
}ARG; 

static int MAT3[10][10];
int r1,c1,r2,c2;

void *mult(void *);
int main()
{
    int MAT1[10][10];
    int MAT2[10][10];
    
    int res=0,p=0,tids=0,n=0,o=0;
    pthread_t tid[100];
    ARG args; 
    int i,j,k;
    
    printf("Enter Number of Rows For Matrix 1 :");
    scanf("%d",&r1);
    
    printf("Enter Number of Columns For Matrix 1 :");
    scanf("%d",&c1);
    
     printf("\nEnter Matrix1 Data: ");
    for(i=0;i<r1;i++)
        for(j=0;j<c1;j++)
            scanf("%d",&MAT1[i][j]);
     
    
    printf("\n");
    
    printf("Enter Numer of Rows For Matrix 2 :");
    scanf("%d",&r2);
    
    printf("Enter Number of Columns For Matrix 2 :");
    scanf("%d",&c2);
    
    printf("\nEnter Matrix 2 Data: ");
    for(i=0;i<r2;i++)
        for(j=0;j<c2;j++)
          scanf("%d",&MAT2[i][j]);
  
    
    if(c1!=r2)
    {
        printf("Wrong Input OR Matrix Multiplication Not Possible!!");
        return 0;
    }
    else
    {
        for(i=0;i<r1;i++)
            for(j=0;j<c2;j++)
                MAT3[i][j]=0;
        
         for(o=0;o<r1;o++)
        {
           sleep(2);
           if(r1==2)
           {         
           for(k=0;k<c1;k++)
           {
                   args.M1=MAT1[o][0];
                   args.M2=MAT1[o][1];
                   args.M3=MAT2[0][0];
                   args.M4=MAT2[1][0];
                   args.M5=MAT2[0][1]; 
                   args.M6=MAT2[1][1]; 
                   args.r1=2;  
                   }
             }        
           
             else if(r1==3)
           {         
                   args.M1=MAT1[o][0];
                   args.M2=MAT1[o][1];
                   args.M3=MAT1[o][2];
                   args.M4=MAT2[0][0];
                   args.M5=MAT2[0][1]; 
                   args.M6=MAT2[0][2];
                   args.M7=MAT2[1][0]; 
                   args.M8=MAT2[1][1];
                   args.M9=MAT2[1][2]; 
                   args.M10=MAT2[2][0]; 
                   args.M11=MAT2[2][1];
                   args.M12=MAT2[2][2];  
                   args.r1=3; 
                   
             } 
            
            pthread_create(&tid[p++],NULL,mult,(void *)&args);
            printf("\nThread %d is Created!!\n",++tids);
        }
       
       n=0;
       for(i=0;i<r1;i++)
        {        
              pthread_join(tid[n++],NULL);       
        }
       
    printf("thread finished ...");
    }
    
    printf("\n Matrix 1 \n");
    
    for(i=0;i<r1;i++)
    {
        for(j=0;j<c1;j++)
        {
            printf("%d \t",MAT1[i][j]);
        }
        printf("\n");
    }    
    
    printf("\n Matrix 2 \n");
    
    for(i=0;i<r2;i++)
    {
        for(j=0;j<c2;j++)
        {
            printf("%d \t",MAT2[i][j]);
        }
        printf("\n");
    }    
    
    printf("\n Multipication of Matrix: \n");
    
    for(i=0;i<r1;i++)
    {
        for(j=0;j<c2;j++)
        {
            printf("%d \t",MAT3[i][j]);
        }
        printf("\n");
    }    
    return 0;
}

static int si=0;

void *mult(void *var)
{
   int res;
   int i=0,j=0;
   
   ARG *tmp=(struct ARG *)var;
                    
        if(tmp->r1==2)  
           {   
                    printf("Values are %d\t %d \t %d\t %d\t %d\t %d\n",tmp->M1,tmp->M2,tmp->M3,tmp->M4,tmp->M5,tmp->M6);
                    MAT3[si][0]=tmp->M1*tmp->M3 + tmp->M2*tmp->M4 ; 
                    MAT3[si][1]=tmp->M1*tmp->M5 + tmp->M2*tmp->M6 ; 
                    //res=0  ;    
               }   
            
            if(tmp->r1==3)
            { 
            printf("Values are %d\t %d \t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\n",tmp->M1,tmp->M2,tmp->M3,tmp->M4,tmp->M5,tmp->M6,tmp->M7,tmp->M8,tmp->M9,tmp->M10,tmp->M11,tmp->M12);
             MAT3[si][0]=tmp->M1*tmp->M4 + tmp->M2*tmp->M7 + tmp->M3*tmp->M10 ;  
             MAT3[si][1]=tmp->M1*tmp->M5 + tmp->M2*tmp->M8 + tmp->M3*tmp->M11 ; 
             MAT3[si][2]=tmp->M1*tmp->M6 + tmp->M2*tmp->M9 + tmp->M3*tmp->M12 ; 
            
   }
   for(i=0;i<r1;i++)
    {
        for(j=0;j<c2;j++)
        {
            printf("%d \t",MAT3[i][j]);
        }
        printf("\n");
    }    
   si=si+1;
   pthread_exit(NULL);   
   
}




