#include <stdio.h>
#include <stdbool.h>

bool bankers_algorithm(char* processes[], int n_processes, int available[], 
                       int max_need[][3], int allocation[][3], int n_resources, 
                       char* safe_sequence[]) {

    // Calculate current need for each process
    int need[n_processes][n_resources];
    for (int i = 0; i < n_processes; i++) {
        for (int j = 0; j < n_resources; j++) {
            need[i][j] = max_need[i][j] - allocation[i][j];
        }
    }

    // Keep track of finished processes
    bool finish[n_processes];
    for (int i = 0; i < n_processes; i++) {
        finish[i] = false;
    }

    // Safe sequence
    int seq_index = 0;

    // Make a copy of available resources
    int work[n_resources];
    for (int i = 0; i < n_resources; i++) {
        work[i] = available[i];
    }

    // Find a safe sequence
    while (seq_index < n_processes) {
        bool found = false;

        // Try to find a process that can be completed
        for (int p_idx = 0; p_idx < n_processes; p_idx++) {
            if (!finish[p_idx]) {
                // Check if all resources are available
                bool can_finish = true;
                for (int j = 0; j < n_resources; j++) {
                    if (need[p_idx][j] > work[j]) {
                        can_finish = false;
                        break;
                    }
                }

                if (can_finish) {
                    // Add allocated resources back to available
                    for (int j = 0; j < n_resources; j++) {
                        work[j] += allocation[p_idx][j];
                    }

                    // Mark process as finished
                    finish[p_idx] = true;
                    safe_sequence[seq_index++] = processes[p_idx];
                    found = true;
                    break;
                }
            }
        }

        // If no process could be found, system is unsafe
        if (!found) {
            return false;
        }
    }

    return true;
}

int main() {
    // Example data
    char* processes[] = {"P0", "P1", "P2", "P3", "P4"};
    int available[] = {3, 3, 2};  // Available instances of resources A, B, C

    int max_need[5][3] = {
        {7, 5, 3},  // P0
        {3, 2, 2},  // P1
        {9, 0, 2},  // P2
        {2, 2, 2},  // P3
        {4, 3, 3}   // P4
    };

    int allocation[5][3] = {
        {0, 1, 0},  // P0
        {2, 0, 0},  // P1
        {3, 0, 2},  // P2
        {2, 1, 1},  // P3
        {0, 0, 2}   // P4
    };

    char* safe_sequence[5];  // Safe sequence of processes

    // Run the Banker's Algorithm
    bool is_safe = bankers_algorithm(processes, 5, available, max_need, allocation, 3, safe_sequence);

    // Print results
    if (is_safe) {
        printf("System is in safe state!\n");
        printf("Safe sequence is: ");
        for (int i = 0; i < 5; i++) {
            printf("%s", safe_sequence[i]);
            if (i < 4) {
                printf(" -> ");
            }
        }
        printf("\n");
    } else {
        printf("System is NOT in safe state!\n");
        printf("Deadlock might occur!\n");
    }

    return 0;
}
