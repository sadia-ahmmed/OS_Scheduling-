
// Write a code for a non-preemptive priority scheduling algorithm.
// a. You will be given three inputs: a floating number p, and two integers n and l.
// b. You have to simulate dynamic process arrival.
// c. You will iterate for 50 steps.
// d. At each step, you will generate a random number denoting the probability of a
// new process arrival. The chance of a new process arriving is p.
// e. When a new process arrives, use a random number to determine how many
// processes will arrive(between 1 and n).
// f. The burst time for \each process will be between 1 and p.
// g. You will have to determine:
// i. Average turnaround time.
// ii. Average waiting time.
// iii. Max turnaround time and process with the max turnaround time.
// iv. Max waiting time and the process with max waiting time.

#include <bits/stdc++.h>
#include <iostream>
#include <cstdlib>
using namespace std;

class Process
{
public:
    int id;
    int arrivalTime, burstTime, waitTime, turnaroundTime, priority, completionTime;

    // assuming there are 4 priority levels
    
    Process(int pid, int arrivalTime)
    {
        this->id = pid;
        this->arrivalTime = arrivalTime;
        this->burstTime = rand() % 20 + 1;
        this->priority = rand() % 4 + 1;
    }
    Process() {}

    void calculateCompletionTime(int current_time)
    {
        completionTime = current_time + burstTime;
    }

    void calculateTurnaroundTime()
    {
        turnaroundTime = completionTime - arrivalTime;
    }

    void calculateWaitingTime()
    {
        waitTime = turnaroundTime - burstTime;
    }
    void printALL()
    {
        cout << "Process id: " << id << "\n"
             << "Priority: " << priority << "\n"
             << "Arrival time: " << arrivalTime << "\n"
             << "Burst time: " << burstTime << "\n"
             << "Turnaround Time:" << turnaroundTime << "\n"
             << "Wait Time: " << waitTime << "\n\n";
    }
};

class Comparator
{
public:
    bool operator()(const Process &a, const Process &b)
    {
        if (a.arrivalTime != b.arrivalTime)
            return a.arrivalTime > b.arrivalTime;
        return a.priority > b.priority;
    }
};

Process isMaxTurnaround(Process &a, Process &b)
{
    if (a.turnaroundTime > b.turnaroundTime)
        return a;
    else
        return b;
}

Process isMaxWait(Process &a, Process &b)
{
    if (a.waitTime > b.waitTime)
        return a;
    else
        return b;
}

int main()
{
    int i, n, l;
    float p;
    srand(10);
    cout << "Probability of a new process arrival:  ";
    cin >> p;
    cout << "Max number of processes in every step: ";
    cin >> n;

    priority_queue<Process, vector<Process>, Comparator> pq;

    int pid = 1;

    for (i = 0; i < 50; i++)
    {
        l = rand() % n; // new processes in every step
        for (int j = 0; j < l; j++)
        {
            Process p = Process(pid, i);
            pq.push(p);
            pid++;
        }
    }

    // priority scheduling the process

    int current_time = 0, size;
    int avg_turnaroundTime = 0, avg_waitTime = 0;
    size = pq.size();
    Process maxTurnaroundProcess = pq.top();
    Process maxWaitProcess = pq.top();
    

    while (!pq.empty())
    {
        Process current_process = pq.top();
        pq.pop();

        current_time = max(current_time, current_process.arrivalTime);

        current_process.calculateCompletionTime(current_time);
        current_process.calculateTurnaroundTime();
        current_process.calculateWaitingTime();

        current_time = current_process.completionTime;

        maxTurnaroundProcess = isMaxTurnaround(maxTurnaroundProcess, current_process);
        maxWaitProcess = isMaxWait(maxWaitProcess, current_process);

        current_process.printALL();
        avg_turnaroundTime += current_process.turnaroundTime/size;
        avg_waitTime += current_process.waitTime/size;
    }

    cout << "Average Turnaround Time: " << avg_turnaroundTime << endl;
    cout << "Average Wait Time: " << avg_waitTime << endl;
    cout << "Process with Maximum Turnaround Time: " << maxTurnaroundProcess.id << " - " << maxTurnaroundProcess.turnaroundTime << " seconds" << endl;
    cout << "Process with Maximum Wait Time: " << maxWaitProcess.id << " - " << maxWaitProcess.waitTime << " seconds" << endl;

    return 0;
}