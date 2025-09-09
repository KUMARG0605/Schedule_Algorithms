🖥️ CPU Scheduling Algorithms

This repository contains C programs that implement various CPU Scheduling Algorithms used in Operating Systems. These algorithms decide the order in which processes are executed by the CPU to optimize metrics like waiting time, turnaround time, and response time.

📌 Implemented Algorithms
1️⃣ FCFS (First Come First Serve)

Non-preemptive.

Processes are executed in the order they arrive.
 
Simple to implement but may cause the convoy effect.

2️⃣ SJF (Shortest Job First)

Non-preemptive.

Process with the smallest burst time is executed first.

Reduces average waiting time but requires burst time prediction.

3️⃣ SRTF (Shortest Remaining Time First)

Preemptive version of SJF.

If a new process arrives with shorter burst time, it preempts the running process.

Provides better response time but harder to implement.

4️⃣ Priority Scheduling

Processes are scheduled based on priority value.

Can be preemptive or non-preemptive.

Risk of starvation, solved using aging.

5️⃣ Round Robin (coming soon)

Preemptive algorithm with a fixed time quantum.

Ensures fairness among all processes.

📊 Metrics Calculated

✅ Waiting Time
✅ Turnaround Time
✅ Response Time
✅ Gantt Chart Representation


🎯 Purpose

This project helps in understanding how different CPU scheduling techniques work, their trade-offs, and their impact on system performance. It is especially useful for:

📘 Operating Systems coursework

📝 Competitive exams

💼 Interview preparation

👨‍💻 Author

G.KUMAR
🎓 Student / Developer interested in Operating Systems & C Programming Java,Python and AI

🌐 GitHub Profile

✨ Feel free to fork, star ⭐, and contribute by adding more scheduling algorithms (like Round Robin, Multilevel Queue, etc.)!
