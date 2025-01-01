#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#define PAGE_SIZE 4096
#define PAGE_ENTRIES 1024
#define True 1
#define False 0
#define bool int

uint8_t physical_memory[1 << 22];
uint32_t *page_directory[PAGE_ENTRIES] = {NULL};
uint32_t page_table[PAGE_ENTRIES][PAGE_ENTRIES] = {{-1}};
int miss = 0;
int hit = 0;
uint32_t count = 0;

void fault(uint32_t pdi, uint32_t pti)
{
    if (page_directory[pdi] == NULL)
    {
        page_directory[pdi] = (uint32_t *)malloc(PAGE_ENTRIES * sizeof(uint32_t));
        for (int i = 0; i < PAGE_ENTRIES; i++)
        {
            page_table[pdi][i] = 0;
        }
        printf("Page table not found! New page table created at %08x.\n", pdi);
    }
    if (page_table[pdi][pti] == -1)
    {
        if (count >= (PAGE_ENTRIES * PAGE_ENTRIES))
        {
            printf("Out of physical memory!\n");
            exit(1);
        }
        page_table[pdi][pti] = count * PAGE_SIZE;
        count++;
        printf("Page not found! New page created at index %u, mapped to physical address 0x%X.\n", pti, page_table[pdi][pti]);
    }
}

uint32_t translate(uint32_t va)
{
    uint32_t pdi = (va >> 22) & 0x3FF;
    uint32_t pti = (va >> 12) & 0x3FF;
    uint32_t offset = va & 0xFFF;
    if (page_directory[pdi] == NULL || page_table[pdi][pti] == -1)
    {
        fault(pdi, pti);
        miss++;
    }
    else
    {
        hit++;
    }
    uint32_t pa = (page_table[pdi][pti]) + offset;
    return pa;
}

uint8_t ld(uint32_t va)
{
    uint32_t pa = translate(va);
    return physical_memory[pa];
}

void store(uint32_t va, uint8_t value)
{
    uint32_t pa = translate(va);
    physical_memory[pa] = value;
}

int main()
{
    bool end = False;
    while (!end)
    {
        printf("Choose from the following:\n");
        printf("1. Load a value\n");
        printf("2. Store a value\n");
        printf("3. Show Hit:Miss\n");
        printf("4. Exit\n");

        int choice;
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
        {
            printf("Enter the virtual address (hexadecimal): ");
            uint32_t va;
            scanf("%08x", &va);
            getchar();
            uint8_t ans = ld(va);
            printf("Value at virtual address 0x%08X is %d\n", va, ans);
            break;
        }
        case 2:
        {
            printf("Enter the virtual address (hexadecimal): ");
            uint32_t st_va;
            scanf("%08x", &st_va);
            getchar();

            printf("Enter the value to store: ");
            uint8_t value;
            scanf("%hhu", &value);
            getchar();

            store(st_va, value);
            printf("%d stored to virtual address 0x%08X\n", value, st_va);
            break;
        }
        case 3:
            printf("Hit:Miss ratio is %d:%d\n", hit, miss);
            break;
        case 4:
            end = True;
            miss = 0;
            hit = 0;
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
