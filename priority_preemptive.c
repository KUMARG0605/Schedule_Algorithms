#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;        // Process ID
    int bt;         // Burst Time
    int at;         // Arrival Time
    int pr;         // Priority (smaller number = higher priority)
    int rt;         // Remaining Time
    int wt;         // Waiting Time
    int tat;        // Turnaround Time
    int ct;         // Completion Time
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Burst Time, Arrival Time, Priority for P%d: ", i + 1);
        scanf("%d %d %d", &p[i].bt, &p[i].at, &p[i].pr);
        p[i].rt = p[i].bt;
    }

    int completed = 0, time = 0;
    float totalWT = 0, totalTAT = 0;

    while (completed != n) {
        int idx = -1;
        int highestPriority = INT_MAX;

        // Find process with highest priority among arrived processes
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0 && p[i].pr < highestPriority) {
                highestPriority = p[i].pr;
                idx = i;
            }
        }

        if (idx != -1) {
            p[idx].rt--; // Execute process for 1 unit
            time++;

            // If process completes
            if (p[idx].rt == 0) {
                completed++;
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;

                totalWT += p[idx].wt;
                totalTAT += p[idx].tat;
            }
        } else {
            // No process available, move time forward
            time++;
        }
    }

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time = %.2f", totalTAT / n);
    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);

    return 0;
}

/*
rguktrkvalley@vikram-564:~/Downloads/OS/lab/output$ ./"priority_preemptive"
Enter number of processes: 3
Enter Burst Time, Arrival Time, Priority for P1: 6 1 3
Enter Burst Time, Arrival Time, Priority for P2: 8 1 2
Enter Burst Time, Arrival Time, Priority for P3: 7 2 1

PID   AT   BT   PR   CT   TAT   WT
P1    1    6    3    21   20    14
P2    1    8    2    14   13    5
P3    2    7    1    9    7     0

Average Turnaround Time = 13.33
Average Waiting Time = 6.33

*/