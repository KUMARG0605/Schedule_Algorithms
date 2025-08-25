#include <stdio.h>

typedef struct {
    int id, at, bt;   // ID, Arrival, Burst
    int ct, tat, wt;  // Completion, Turnaround, Waiting
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
    }

    // Sort by arrival time (FCFS order)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int time = 0;
    double avgWT = 0, avgTAT = 0;

    for (int i = 0; i < n; i++) {
        if (time < p[i].at)  // If CPU idle, jump to arrival time
            time = p[i].at;

        p[i].ct = time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt  = p[i].tat - p[i].bt;

        time = p[i].ct; // update time
        avgWT  += p[i].wt;
        avgTAT += p[i].tat;
    }

    // Print results
    printf("\n--- FCFS Scheduling ---\n");
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
Enter Arrival Time & Burst Time for P1: 0 5
Enter Arrival Time & Burst Time for P2: 1 3
Enter Arrival Time & Burst Time for P3: 2 8


--- FCFS Scheduling ---
PID     AT      BT      CT      TAT     WT
P1      0       5       5       5       0
P2      1       3       8       7       4
P3      2       8      16      14       6

Average Turnaround Time: 8.67
Average Waiting Time   : 3.33

rguktrkvalley@vikram-564:~/Downloads/OS/lab/output$ ./"first_come_first_search"
Enter number of processes: 5  
Enter Arrival Time & Burst Time for P1: 2 1
Enter Arrival Time & Burst Time for P2: 1 5
Enter Arrival Time & Burst Time for P3: 4 1
Enter Arrival Time & Burst Time for P4: 0 6
Enter Arrival Time & Burst Time for P5: 2 3

--- FCFS Scheduling ---
PID     AT      BT      CT      TAT     WT
P4      0       6       6       6       0
P2      1       5       11      10      5
P1      2       1       12      10      9
P5      2       3       15      13      10
P3      4       1       16      12      11

Average Turnaround Time: 10.20
Average Waiting Time   : 7.00
rguktrkvalley@vikram-564:~/Downloads/OS/lab/output$ 
*/