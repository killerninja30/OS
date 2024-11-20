#include <stdio.h>
#include <stdlib.h>

void optimal_page_replacement(int pages[], int n, int capacity) {
    int memory[capacity];
    int page_faults = 0;

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
                // Find the page that will not be used for the longest time
                int future_indices[capacity];
                for (int j = 0; j < capacity; j++) {
                    future_indices[j] = -1;
                    for (int k = i + 1; k < n; k++) {
                        if (memory[j] == pages[k]) {
                            future_indices[j] = k;
                            break;
                        }
                    }
                    if (future_indices[j] == -1) {
                        future_indices[j] = n;  // If the page is not used in the future, set a large index
                    }
                }

                // Replace the page that won't be used for the longest time
                int max_index = 0;
                for (int j = 1; j < capacity; j++) {
                    if (future_indices[j] > future_indices[max_index]) {
                        max_index = j;
                    }
                }
                memory[max_index] = page;
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

    printf("Optimal Page Faults: %d\n", page_faults);
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    optimal_page_replacement(pages, n, capacity);
    return 0;
}
