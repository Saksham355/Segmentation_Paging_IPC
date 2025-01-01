




## Question 1

### Description

Perform parallel merge sort on a 16-element array. The 16-element array would be divided into two 8-element arrays, and each one would be passed to a child process. Similarly, the children would pass 4-element arrays to their children and so on. Each process will wait for its children and then merge the resulting arrays using a merge operation. Use pipes to pass data among processes.

### Files

- `q1.c`: Contains the main function and the implementation.

### Instructions

1. Define a 16-element unsorted array in the code.
2. Divide the array into two 8-element arrays and pass them to child processes.
3. Repeat the process until 4-element arrays are reached.
4. Each process will wait for its children and then merge the arrays using pipes.
5. Print the initial unsorted array and the final sorted array.


## Question 2

### Description

Simulate an operating system's memory management using segmentation. Your task is to simulate the process of translating logical addresses to physical addresses using the concept of segmentation and handle conditions where a segmentation fault occurs.

### Files

- `q2.c`: Contains the main function and the implementation.


### Instructions

1. The system has three segments: Code, Heap, and Stack.
2. Each segment has a base and a limit (bounds).
3. Physical memory is 64KB.
4. Segmentation fault is raised if the offset exceeds the segment's limit.
5. Use the pseudocode from Chapter 16 for address translation.
6. User enters a 16-bit logical address in hex format.



## Question 3

### Description

Simulate paging-based memory management and address translation using a Page Table and Translation Lookaside Buffer (TLB). Demonstrate how logical addresses are translated into physical addresses using a page table and how the TLB serves as a cache.

### Files

- `q3.c`: Contains the main function and the implementation.
### Instructions

1. Implement a page table that maps virtual page numbers (VPNs) to physical frame numbers (PFNs).
2. Use a fixed page size of 4KB and 64KB of total memory.
3. Simulate a TLB that caches recent translations.
4. Consult the TLB first for translations (TLB hit or miss).
5. On a TLB miss, access the page table to fetch the PFN and update the TLB.
6. Use the pseudocode from Chapter 19 for address translation.
7. User enters a 16-bit logical address in hex format.


## Question 4

### Description

Simulate address translation using a two-level page table with a page directory for virtual memory management.

### Files

- `q4.c`: Contains the main function and the implementation.

### Instructions

1. Implement a two-level page table structure with a Page Directory (PD) and Page Tables.
2. Virtual address is divided into Page Directory Index (10 bits), Page Table Index (10 bits), and Offset (12 bits).
3. Use the configuration:
   - Virtual Address Length: 32-bit
   - Page Size: 4KB
   - Page Table Entries: 1024 entries (each entry is 4B)
4. Implement API functions `load(uint32_t va)` and `store(uint32_t va)`.
5. Simulate memory access and handle page faults.



## Question 5

### Description

Simulate a memory management system that demonstrates page faults and handles them using the clock algorithm for page replacement. Consider the use/reference bit and the dirty bit associated with each page.

### Files

- `q5.c`: Contains the main function and the implementation.

### Instructions

1. Simulate a memory of N pages using a fixed-size page table.
2. Input:
   - `num_frames`: Number of available page slots (frames).
   - `page_requests`: A string representing page requests (e.g., "0,1,1,2,4,2").
3. Output:
   - Total page faults
   - Total page hits
   - Hit rate
4. Implement the clock algorithm to replace pages and update the reference and dirty bits.
5. Print the total faults, total page hits, and hit rate.









