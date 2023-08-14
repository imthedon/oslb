#include <stdio.h>


void diskcscan(int disk[],int n,int h)
{
    int key;
    int seeksum = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (disk[i] > disk[j])
            {
                int temp = disk[j];
                disk[j] = disk[i];
                disk[i] = temp;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (disk[i] == h)
        {
            key = i;
            break;
        }
    }

    printf("Disk sequence :\n");
    int i=key+1;
    printf("%d",disk[key]);
    while(i!=key)
    {
        printf(" => %d",disk[i]);
        if(i==0)
        {
            seeksum=seeksum+199;
        }
        else
        {
            seeksum=seeksum+disk[i]-disk[i-1];
        }
        i=(i+1)%n;
    }
    printf("\n");
    printf("total seektime=%d\n",seeksum);
   

}






int main()
{

    int h, n;
    printf("Enter the head position: ");
    scanf("%d", &h);
    printf("Enter the number of disk requests");
    scanf("%d", &n);
    int disk[n + 5];
    printf("Enter the disk requests :\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &disk[i]);
    }
    disk[n++] = 0;
    disk[n++] = 199;
    disk[n++] = h;
    
    diskcscan(disk,n,h);
    return 0;
}
