#include <stdio.h>
#include <limits.h>

typedef struct {
    int id, at, bt, pr;  // ID, Arrival, Burst, Priority
    int ct, tat, wt;     // Completion, Turnaround, Waiting
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
        printf("Enter Arrival, Burst, Priority for P%d: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
        p[i].done = 0;
    }

    int time = 0, completed = 0;
    double avgWT = 0, avgTAT = 0;

    // Start from earliest arrival
    int earliest = INT_MAX;
    for (int i = 0; i < n; i++)
        if (p[i].at < earliest) earliest = p[i].at;
    time = earliest;

    while (completed < n) {
        int idx = -1, bestPr = INT_MAX;

        // Select highest priority (lowest pr value) among arrived
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time) {
                if (p[i].pr < bestPr) {
                    bestPr = p[i].pr;
                    idx = i;
                }
            }
        }

        // If no process ready, jump to next arrival
        if (idx == -1) {
            int nextAt = INT_MAX;
            for (int i = 0; i < n; i++)
                if (!p[i].done && p[i].at < nextAt) nextAt = p[i].at;
            time = nextAt;
            continue;
        }

        // Execute process (non-preemptive → full burst)
        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt  = p[idx].tat - p[idx].bt;
        p[idx].done = 1;

        avgWT  += p[idx].wt;
        avgTAT += p[idx].tat;
        completed++;
    }

    // Print results
    printf("\n--- Priority Scheduling (Non-Preemptive) ---\n");
    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\nAverage Turnaround Time: %.2f", avgTAT / n);
    printf("\nAverage Waiting Time   : %.2f\n", avgWT / n);

    return 0;
}

/*
Enter number of processes: 4
Enter Arrival, Burst, Priority for P1: 0 5 2
Enter Arrival, Burst, Priority for P2: 1 3 1
Enter Arrival, Burst, Priority for P3: 2 8 4
Enter Arrival, Burst, Priority for P4: 3 6 3


--- Priority Scheduling (Non-Preemptive) ---
PID     AT      BT      PR      CT      TAT     WT
P1      0       5       2       5       5       0
P2      1       3       1       8       7       4
P4      3       6       3      14      11       5
P3      2       8       4      22      20      12

Average Turnaround Time: 10.75
Average Waiting Time   : 5.25


rguktrkvalley@vikram-564:~/Downloads/OS/lab/output$ ./"priority_non_preemptive"
Enter number of processes: 4
Enter Arrival, Burst, Priority for P1: 0 10 5
Enter Arrival, Burst, Priority for P2: 1 6 4
Enter Arrival, Burst, Priority for P3: 3 2 2
Enter Arrival, Burst, Priority for P4: 5 4 0

--- Priority Scheduling (Non-Preemptive) ---
PID     AT      BT      PR      CT      TAT     WT
P1      0       10      5       10      10      0
P2      1       6       4       22      21      15
P3      3       2       2       16      13      11
P4      5       4       0       14      9       5

Average Turnaround Time: 13.25
Average Waiting Time   : 7.75
rguktrkvalley@vikram-564:~/Downloads/OS/lab/output$ ./"priority_non_preemptive"
Enter number of processes: 7
Enter Arrival, Burst, Priority for P1: 0 8 3
Enter Arrival, Burst, Priority for P2: 1 2 4
Enter Arrival, Burst, Priority for P3: 3 4 4
Enter Arrival, Burst, Priority for P4: 4 1 5
Enter Arrival, Burst, Priority for P5: 5 6 2
Enter Arrival, Burst, Priority for P6: 6 5 6
Enter Arrival, Burst, Priority for P7: 1 10 1

--- Priority Scheduling (Non-Preemptive) ---
PID     AT      BT      PR      CT      TAT     WT
P1      0       8       3       8       8       0
P2      1       2       4       26      25      23
P3      3       4       4       30      27      23
P4      4       1       5       31      27      26
P5      5       6       2       24      19      13
P6      6       5       6       36      30      25
P7      1       10      1       18      17      7

Average Turnaround Time: 21.86
Average Waiting Time   : 16.71
*/