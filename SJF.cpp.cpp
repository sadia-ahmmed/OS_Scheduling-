
#include <bits/stdc++.h>
#include <iostream>
#include <cstdlib>
using namespace std;

class Process
{
public:
    int id;
    int arrivalTime, burstTime, waitTime, turnaroundTime=0, priority, completionTime;

    
    Process(int pid, int arrivalTime)
    {
        this->id = pid;
        this->arrivalTime = arrivalTime;
        this->burstTime = rand() % 5 + 1;
       
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
             << "Arrival time: " << arrivalTime << "\n"
             << "Burst time: " << burstTime << "\n"
             << "Completion time: "<<completionTime<<"\n"
             << "Turnaround Time:" << turnaroundTime << "\n"
             << "Wait Time: " << waitTime << "\n\n";
    }
};

class Comparator
{
public:
    bool operator()( Process &a,  Process &b)
    {
        if (a.arrivalTime != b.arrivalTime)
            return a.arrivalTime > b.arrivalTime;
        return a.burstTime > b.burstTime;
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
    
    // inserting to the priority  queue 

    for (i = 0; i < 3; i++)
    {
        l =2;
        //  rand() % n; // new processes in every step
        for (int j = 0; j < l; j++)
        {
            Process p = Process(pid, i);
            pq.push(p);
            pid++;
        }
    }

    // scheduling the process

    int current_time = 0, size;
    int avg_turnaroundTime = 0, avg_waitTime = 0;
    size = pq.size();
    Process maxTurnaroundProcess = pq.top();
    Process maxWaitProcess = pq.top();

    // priority_queue<Process, vector<Process>, Comparator> pq_temp;

    while (!pq.empty())
    {

        Process current_process = pq.top();
        pq.pop();

        current_time = max(current_time, current_process.arrivalTime);

        current_process.calculateCompletionTime(current_time);
        current_process.calculateTurnaroundTime();
        current_process.calculateWaitingTime();

        current_time = current_process.completionTime;
        // cout<<current_time<<endl;
        maxTurnaroundProcess = isMaxTurnaround(maxTurnaroundProcess, current_process);
        maxWaitProcess = isMaxWait(maxWaitProcess, current_process);

        current_process.printALL();

        avg_turnaroundTime += current_process.turnaroundTime;
        avg_waitTime += current_process.waitTime;
    }

    cout << "Average Turnaround Time: " << avg_turnaroundTime/size<< endl;
    cout << "Average Wait Time: " << avg_waitTime/size << endl;
    cout << "Process with Maximum Turnaround Time: " << maxTurnaroundProcess.id << " - " << maxTurnaroundProcess.turnaroundTime << " seconds" << endl;
    cout << "Process with Maximum Wait Time: " << maxWaitProcess.id << " - " << maxWaitProcess.waitTime << " seconds" << endl;

    return 0;
}