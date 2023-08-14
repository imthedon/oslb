// implement disk scheduling using scan algorithm
#include <stdio.h>
void diskscan(int disk[], int n, int h)
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
    printf("The disk sequence is : \n");
    if (h < 199 - h)
    {
        for (int i = key; i >= 0; i--)
        {
            printf("%d ", disk[i]);
        }
        for (int i = key; i > 0; i--)
        {
            seeksum += disk[i] - disk[i - 1];
        }
        seeksum = seeksum + disk[key + 1];
        for (int i = key+1; i < n; i++)
        {
            printf("%d ", disk[i]);
        }
        for (int i = key+1; i < n - 1; i++)
        {
            seeksum += disk[i + 1] - disk[i];
        }     
    }
    else
    {
        for (int i = key; i < n; i++)
        {
            printf("%d ", disk[i]);
        }
        for (int i = key; i < n - 1; i++)
        {
            seeksum += disk[i + 1] - disk[i];
        }
        seeksum = seeksum + 199 - disk[key - 1];
        for (int i = key - 1; i >= 0; i--)
        {
            printf("%d ", disk[i]);
        }
        for (int i = key - 1; i > 0; i--)
        {
            seeksum += disk[i] - disk[i - 1];
        }
    }

    printf("\n");
    printf("The total seek time is : %d\n", seeksum);
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

    diskscan(disk, n, h);
    return 0;
}
