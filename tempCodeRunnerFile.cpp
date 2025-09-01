#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent a process
struct Process {
    int pid;           // Process ID
    int arrivalTime;   // Arrival time of the process
    int burstTime;     // Burst time (time required to complete)
    int remainingTime; // Remaining time for Round Robin
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

// FCFS (First-Come-First-Served) Scheduling
void FCFS(vector<Process>& processes) {
    int n = processes.size();
    int currentTime = 0;

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), [](Process& a, Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    for (int i = 0; i < n; i++) {
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }
        processes[i].completionTime = currentTime + processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;

        currentTime = processes[i].completionTime;
    }
}

// SJF (Shortest Job First) Scheduling
void SJF(vector<Process>& processes) {
    int n = processes.size();
    int currentTime = 0;
    vector<bool> completed(n, false);
    int completedProcesses = 0;

    while (completedProcesses < n) {
        int shortestJob = -1;
        int minBurstTime = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!completed[i] && processes[i].arrivalTime <= currentTime && processes[i].burstTime < minBurstTime) {
                shortestJob = i;
                minBurstTime = processes[i].burstTime;
            }
        }

        if (shortestJob != -1) {
            processes[shortestJob].completionTime = currentTime + processes[shortestJob].burstTime;
            processes[shortestJob].turnaroundTime = processes[shortestJob].completionTime - processes[shortestJob].arrivalTime;
            processes[shortestJob].waitingTime = processes[shortestJob].turnaroundTime - processes[shortestJob].burstTime;
            currentTime = processes[shortestJob].completionTime;
            completed[shortestJob] = true;
            completedProcesses++;
        } else {
            currentTime++; // If no process can be executed, increment time
        }
    }
}

// Round Robin Scheduling
void RoundRobin(vector<Process>& processes, int quantum) {
    int n = processes.size();
    int currentTime = 0;
    queue<int> readyQueue;

    for (int i = 0; i < n; i++) {
        processes[i].remainingTime = processes[i].burstTime;
    }

    int completedProcesses = 0;
    while (completedProcesses < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                readyQueue.push(i);
            }
        }

        if (!readyQueue.empty()) {
            int idx = readyQueue.front();
            readyQueue.pop();
            int timeSlice = min(quantum, processes[idx].remainingTime);

            processes[idx].remainingTime -= timeSlice;
            currentTime += timeSlice;

            if (processes[idx].remainingTime == 0) {
                processes[idx].completionTime = currentTime;
                processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
                processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
                completedProcesses++;
            }

            // Push back the process if it still has remaining time
            if (processes[idx].remainingTime > 0) {
                readyQueue.push(idx);
            }
        } else {
            currentTime++; // No process is ready, increment time
        }
    }
}

// Function to display the process details
void displayResults(vector<Process>& processes) {
    cout << "PID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (auto& process : processes) {
        cout << process.pid << "\t" << process.arrivalTime << "\t\t" << process.burstTime
             << "\t\t" << process.completionTime << "\t\t" << process.turnaroundTime << "\t\t" << process.waitingTime << endl;
    }
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Input for processes
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
    }

    int choice;
    cout << "\nChoose Scheduling Algorithm:\n";
    cout << "1. FCFS (First-Come-First-Served)\n";
    cout << "2. SJF (Shortest Job First)\n";
    cout << "3. Round Robin (Enter time quantum)\n";
    cout << "Enter your choice (1/2/3): ";
    cin >> choice;

    if (choice == 1) {
        FCFS(processes);
    } else if (choice == 2) {
        SJF(processes);
    } else if (choice == 3) {
        int quantum;
        cout << "Enter time quantum for Round Robin: ";
        cin >> quantum;
        RoundRobin(processes, quantum);
    } else {
        cout << "Invalid choice! Exiting...\n";
        return 1;
    }

    // Display the results
    displayResults(processes);

    return 0;
}
