#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void translateAddress(uint16_t logicalAddress) {
    
    uint16_t CodeBase =0x8000;
    uint16_t CodeBounds =0x0800;
    
    uint16_t HeapBase= 0x8800; 
    uint16_t HeapBounds= 0x0C00;
    
    uint16_t StackBase =0x7000;
    uint16_t StackBounds =0x0800; 
    
    uint16_t segmentSelector = (logicalAddress) >> 14; 
    uint16_t offset = logicalAddress & 0x0FFF; 

    uint16_t physicalAddress;

    if (segmentSelector == 0) { 
        if (offset < CodeBounds) {
            physicalAddress = CodeBase + offset;
            printf("Physical Address: 0x%04X\n", physicalAddress);
        } 
        else {
            printf("Segmentation Fault (Code Segment)\n");
        }
    } 
    
    else if (segmentSelector == 1) { 
        if (offset < HeapBounds) {
            physicalAddress = HeapBase + offset;
            printf("Physical Address: 0x%04X\n", physicalAddress);
        } 
        else {
            printf("Segmentation Fault (Heap Segment)\n");
        }
    } 
    
    else if (segmentSelector == 2) { 
        if (offset < StackBounds) {
            physicalAddress = StackBase - offset;
            printf("Physical Address: 0x%04X\n", physicalAddress);
        } 
        else {
            printf("Segmentation Fault (Stack Segment)\n");
        }
    } 
    
    else {
        printf("Invalid segment selector\n");
    }
}


int main() {
    char logicalAddressInput[5];
    uint16_t logicalAddress;

    printf("Enter a 16-bit logical address in hex (e.g., a56f): ");
    scanf("%4s", logicalAddressInput);

    logicalAddress = (uint16_t)strtol(logicalAddressInput, NULL, 16);

    translateAddress(logicalAddress);

    return 0;
}
