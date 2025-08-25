#include <stdio.h>
#include <limits.h>

// Process structure
typedef struct {
    int id, at, bt;      // ID, Arrival, Burst
    int rt;              // Remaining Time
    int ct, wt, tat;     // Completion, Waiting, Turnaround
    int done;
} Process;

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];
    int totalBT = 0, minAT = INT_MAX;

    // Input process details
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time & Burst Time for P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;    // Initially remaining = burst
        p[i].done = 0;
        totalBT += p[i].bt;
        if (p[i].at < minAT) minAT = p[i].at;
    }

    int time = minAT, completed = 0;
    double avgWT = 0, avgTAT = 0;

    // Simulation (unit by unit)
    while (completed < n) {
        int idx = -1, bestRT = INT_MAX;

        // Choose process with shortest remaining time
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time && p[i].rt < bestRT) {
                bestRT = p[i].rt;
                idx = i;
            }
        }

        // If no process is ready, jump to next arrival
        if (idx == -1) {
            int nextAt = INT_MAX;
            for (int i = 0; i < n; i++)
                if (!p[i].done && p[i].at < nextAt) nextAt = p[i].at;
            time = nextAt;
            continue;
        }

        // Run chosen process for 1 unit
        p[idx].rt--;
        time++;

        // If process finishes
        if (p[idx].rt == 0) {
            p[idx].done = 1;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt  = p[idx].tat - p[idx].bt;

            avgWT  += p[idx].wt;
            avgTAT += p[idx].tat;
            completed++;
        }
    }

    // Output results
    printf("\n--- SRTF (Preemptive SJF) Scheduling ---\n");
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
Enter number of processes: 3
Enter Arrival Time & Burst Time for P1: 0 7
Enter Arrival Time & Burst Time for P2: 2 4
Enter Arrival Time & Burst Time for P3: 4 1


--- SRTF (Preemptive SJF) Scheduling ---
PID     AT      BT      CT      TAT     WT
P1      0       7      12      12       5
P2      2       4       8       6       2
P3      4       1       5       1       0

Average Turnaround Time: 6.33
Average Waiting Time   : 2.33


rguktrkvalley@vikram-564:~/Downloads/OS/lab/output$ ./"shortest_remain_time_first"
Enter number of processes: 5
Enter Arrival Time & Burst Time for P1: 2 1
Enter Arrival Time & Burst Time for P2: 1 5
Enter Arrival Time & Burst Time for P3: 4 1
Enter Arrival Time & Burst Time for P4: 0 6
Enter Arrival Time & Burst Time for P5: 2 3

--- SRTF (Preemptive SJF) Scheduling ---
PID     AT      BT      CT      TAT     WT
P1      2       1       3       1       0
P2      1       5       11      10      5
P3      4       1       5       1       0
P4      0       6       16      16      10
P5      2       3       7       5       2

Average Turnaround Time: 6.60
Average Waiting Time   : 3.40
rguktrkvalley@vikram-564:~/Downloads/OS/lab/output$ 
*/