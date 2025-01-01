#include <stdio.h>
#include <stdlib.h>
#define bool int

struct page
{
    int page_number;
    int reference_bit;
    int dirty_bit;
};

int main()
{
    int frames;
    printf("Enter the number of frames: ");
    scanf("%d", &frames);
    struct page *p = (struct page *)malloc(frames * sizeof(struct page));
    for (int i = 0; i < frames; i++)
    {
        p[i].page_number = -1;
        p[i].reference_bit = 0;
        p[i].dirty_bit = 0;
    }

    int requests;
    printf("Enter the number of page requests: ");
    scanf("%d", &requests);
    int hit = 0;
    int miss = 0;

    for (int i = 0; i < requests; i++)
    {
        bool status = 0;
        int page;
        printf("Enter page number: ");
        scanf("%d", &page);

        for (int j = 0; j < frames; j++)
        {
            if (p[j].page_number == page)
            {
                hit++;
                status = 1;
                p[j].reference_bit = 1;
                break;
            }
        }

        if (status == 1)
        {
            continue;
        }
        else
        {
            miss++;
            for (int j = 0; j < frames; j++)
            {
                if (p[j].page_number == -1 || p[j].reference_bit == 0)
                {
                    p[j].page_number = page;
                    p[j].reference_bit = 1;
                    break;
                }
                else
                {
                    p[j].reference_bit = 0;
                }
            }
        }
    }

    printf("Hits: %d\n", hit);
    printf("Misses: %d\n", miss);
    printf("Hit rate: %.2f\n", (float)hit / requests);

    free(p);
    return 0;
}
