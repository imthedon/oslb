#include <stdio.h>

typedef struct
{
    int size;
    int occupied;
}block;

typedef struct
{
    int size;
    int allocated;
}process;

void firstfit(block m[],process p[],int mno,int pno)
{
    for(int i=0;i<pno;i++)
    {
        for(int j=0;j<mno;j++)
        {
            if (m[j].size>p[i].size && m[j].occupied==0)
            {
                p[i].allocated=j+1;
                m[j].occupied=1;
                break;
            }
        }
    }
}



void bestfit(block m[],process p[],int mno,int pno)
{
   for(int i=0;i<pno;i++)
    {
        int bestfit=-1;
        for(int j=0;j<mno;j++)
        {
            if (m[j].size>p[i].size && m[j].occupied==0)
            {
                if(bestfit==-1 || m[j].size<m[bestfit].size)
                {
                    bestfit=j;
                }
                
            }
        }
        if(bestfit!=-1)
        {
            p[i].allocated=bestfit+1;
            m[bestfit].occupied=1;

        }
    } 
}

void worstfit(block m[],process p[],int mno,int pno)
{
   for(int i=0;i<pno;i++)
    {
        int worstfit=-1;
        for(int j=0;j<mno;j++)
        {
            if (m[j].size>p[i].size && m[j].occupied==0)
            {
                if(worstfit==-1 || m[j].size>m[worstfit].size)
                {
                    worstfit=j;
                }
                
            }
        }
        if(worstfit!=-1)
        {
            p[i].allocated=worstfit+1;
            m[worstfit].occupied=1;

        }
    } 
}





int main()
{
    int pno,mno;
    printf("Enter the number of blocks and processes :");
    scanf("%d %d",&mno,&pno);
    process p[pno];
    block m[mno];
    for(int i=0;i<mno;i++)
    {
        printf("Enter the memory block value of block %d :",i+1);
        scanf("%d",&m[i].size);
        m[i].occupied=0;
    }
    for(int i=0;i<pno;i++)
    {
        printf("Enter the process values of process %d :",i+1);
        scanf("%d",&p[i].size);
        p[i].allocated=-1;
    }


    //firstfit(m,p,mno,pno);
    //bestfit(m,p,mno,pno);
    worstfit(m,p,mno,pno);
    




    printf("process no \t process size \t block allocated\n");
    for(int i=0;i<pno;i++)
    {
        if(p[i].allocated !=-1)
        {
            printf("%d\t\t%d\t\t%d\n",i+1,p[i].size,p[i].allocated);
        }
        else
        {
            printf("%d\t\t%d\t\tNot allocated\n",i+1,p[i].size);
        } 
        
    }


}
