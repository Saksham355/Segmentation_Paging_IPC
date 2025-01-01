#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#define bool int
#define true 1
#define false 0

#define PAGE_SIZE 4096
#define TOTAL_MEMORY 65536
#define NUM_PAGES (TOTAL_MEMORY / PAGE_SIZE)
#define TLB_SIZE 4

struct TLBEntry
{
    uint16_t vpn;
    uint16_t pfn;
    bool valid;
};

uint16_t page_table[NUM_PAGES];
struct TLBEntry tlb[TLB_SIZE];
uint8_t physical_memory[TOTAL_MEMORY];
int tlb_hit = 0;
int tlb_miss = 0;

int look_in_tlb(uint16_t vpn)
{
    for (int i = 0; i < TLB_SIZE; i++)
    {
        if (tlb[i].valid && tlb[i].vpn == vpn)
        {
            return tlb[i].pfn;
        }
    }
    return -1;
}

void add_in_tlb(uint16_t vpn, uint16_t pfn)
{
    for (int i = TLB_SIZE - 1; i > 0; i--)
    {
        tlb[i] = tlb[i - 1];
    }
    tlb[0].vpn = vpn;
    tlb[0].pfn = pfn;
    tlb[0].valid = true;
}

uint16_t translate(uint16_t logical_address)
{
    uint16_t vpn = logical_address / PAGE_SIZE;
    uint16_t offset = logical_address % PAGE_SIZE;

    int pfn = look_in_tlb(vpn);

    if (pfn == -1)
    {
        tlb_miss++;
        printf("TLB Miss \n");
        pfn = page_table[vpn];
        add_in_tlb(vpn, pfn);
    }
    else
    {

        tlb_hit++;
        printf("TLB Hit\n");
    }

    return (pfn * PAGE_SIZE) + offset;
}

int main()
{
    for (int i = 0; i < NUM_PAGES; i++)
    {
        page_table[i] = i;
    }
    for (int i = 0; i < TLB_SIZE; i++)
    {
        tlb[i].valid = false;
    }

    bool end = false;
    while (!end)
    {
        printf("Choose from the following:\n");
        printf("1. Show Physical address\n");
        printf("2. Show Hit:Miss\n");
        printf("3. Exit\n");

        int choice;
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
        {
            printf("Enter the virtual address (hexadecimal): ");
            uint16_t va;
            scanf("%04x", &va);
            getchar();
            uint16_t ans = translate(va);
            printf("Physical address: 0x%04X\n", ans);

            break;
        }
        case 2:
            printf("TLB Hit:Miss is %d:%d\n", tlb_hit, tlb_miss);
            break;
        case 3:
            end = true;
            tlb_hit = 0;
            tlb_miss = 0;
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
