# 🖥️ Process Scheduling Algorithms in C++  

This project implements three **classic CPU process scheduling algorithms** in C++:  

1. **First-Come-First-Served (FCFS)**  
2. **Shortest Job First (SJF)**  
3. **Round Robin (RR)**  

It allows users to input processes with **arrival times** and **burst times**, then select a scheduling algorithm to simulate.  

##  Features  

-  **First-Come-First-Served (FCFS)**: Processes are executed in the order they arrive.  
-  **Shortest Job First (SJF)**: Selects the process with the smallest burst time first.  
-  **Round Robin (RR)**: Allocates CPU time slices (quantum) to processes in a circular manner.  
-  Calculates for each process:  
  - Completion Time  
  - Turnaround Time  
  - Waiting Time  
-  Displays results in a tabular format.  

## Tech Stack  

- **Language**: C++  
- **Concepts**: Process Scheduling, Queues, CPU Time Management  


   ```bash
   g++ scheduling.cpp -o scheduling
