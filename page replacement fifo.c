#include <stdio.h>
#include <stdlib.h>

void fifo_page_replacement(int pages[], int n, int capacity) {
    int memory[capacity];
    int page_faults = 0, front = 0;

    // Initialize memory as empty
    for (int i = 0; i < capacity; i++) {
        memory[i] = -1;  // Empty slots are represented by -1
    }

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in memory
        for (int j = 0; j < capacity; j++) {
            if (memory[j] == page) {
                found = 1;
                break;
            }
        }

        // Page fault occurs if page is not found
        if (!found) {
            if (page_faults < capacity) {
                memory[page_faults] = page;
            } else {
                // FIFO: Remove the first page and add the new one
                memory[front] = page;
                front = (front + 1) % capacity;
            }
            page_faults++;
        }

        // Print the memory state, avoiding printing -1
        printf("Memory: ");
        for (int j = 0; j < capacity; j++) {
            if (memory[j] != -1) {  // Only print non-empty slots
                printf("%d ", memory[j]);
            }
        }
        printf("\n");
    }

    printf("FIFO Page Faults: %d\n", page_faults);
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    fifo_page_replacement(pages, n, capacity);
    return 0;
}
