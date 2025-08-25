#include <stdio.h>
#include <limits.h>

// Structure to hold process details
typedef struct {
    int id, at, bt;      // Process ID, Arrival Time, Burst Time
    int ct, wt, tat;     // Completion, Waiting, Turnaround Time
    int done;
} Process;

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time & Burst Time for P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].done = 0;
    }

    int time = 0, completed = 0;
    double avgWT = 0, avgTAT = 0;

    // Start from earliest arrival
    int earliest = INT_MAX;
    for (int i = 0; i < n; i++)
        if (p[i].at < earliest) earliest = p[i].at;
    time = earliest;

    // Scheduling loop
    while (completed < n) {
        int idx = -1, bestBT = INT_MAX;

        // Find shortest job among arrived & not done
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time && p[i].bt < bestBT) {
                bestBT = p[i].bt;
                idx = i;
            }
        }

        // If no process has arrived, move time to next arrival
        if (idx == -1) {
            int nextAt = INT_MAX;
            for (int i = 0; i < n; i++)
                if (!p[i].done && p[i].at < nextAt) nextAt = p[i].at;
            time = nextAt;
            continue;
        }

        // Run process till completion
        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt  = p[idx].tat - p[idx].bt;
        p[idx].done = 1;

        avgWT  += p[idx].wt;
        avgTAT += p[idx].tat;
        completed++;
    }

    // Output results
    printf("\n--- SJF (Non-preemptive) Scheduling ---\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\nAverage Turnaround Time: %.2f", avgTAT / n);
    printf("\nAverage Waiting Time   : %.2f\n", avgWT / n);

    return 0;
}


/*


Enter number of processes: 5
Enter Arrival Time & Burst Time for P1: 2 1
Enter Arrival Time & Burst Time for P2: 1 5
Enter Arrival Time & Burst Time for P3: 4 1
Enter Arrival Time & Burst Time for P4: 0 6
Enter Arrival Time & Burst Time for P5: 2 3

--- SJF (Non-preemptive) Scheduling ---
PID     AT      BT      CT      TAT     WT
P1      2       1       7       5       4
P2      1       5       16      15      10
P3      4       1       8       4       3
P4      0       6       6       6       0
P5      2       3       11      9       6

Average Turnaround Time: 7.80
Average Waiting Time   : 4.60


Enter number of processes: 3
Enter Arrival Time & Burst Time for P1: 0 7
Enter Arrival Time & Burst Time for P2: 2 4
Enter Arrival Time & Burst Time for P3: 4 1


--- SJF (Non-preemptive) Scheduling ---
PID     AT      BT      CT      TAT     WT
P1      0       7       7       7       0
P3      4       1       8       4       3
P2      2       4      12      10       6

Average Turnaround Time: 7.00
Average Waiting Time   : 3.00

*/