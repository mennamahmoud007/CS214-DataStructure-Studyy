#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
using namespace std;
/*Problem 4: Round Robin Scheduler Implementation [3 marks] 
Implement a C++ program that simulates Round Robin CPU scheduling. The program 
must handle processes with different arrival times and manage a Ready Queue to 
determine the execution order. 
C++ Logic Requirements 
1. Input: Use int for the number of processes and the time quantum. Use a 
struct or class to store process details ($AT$, $BT$, etc.). 
2. The Queue: Use std::queue<int> from the <queue> library to manage 
process IDs. 
3. The Loop: Use a while loop that continues as long as the queue is not empty 
or there are processes yet to arrive. 
4. The Comparison: At each time step, check if new processes have arrived 
before pushing a preempted process back into the queue. 
Sample 1:  
Input Format: 
Time Quantum: 2 
Number of Processes: 3 
Arrival Time, Needed Time P1: 0 5 
Arrival Time, Needed Time P2: 1 3 
Arrival Time, Needed Time P3: 2 1 
Output Format: 
Queue updates:  
[ P1 ]  
[ P2, P3, P1 ]  
[ P3, P1, P2 ]  
[ P1, P2 ]  
[ P2, P1 ]  
[ P1 ]  
[ Empty ] 
Process 
Completion Time 
Turnaround Time 
Waiting Time 
P1 
P2 
P3 
9 
8 
5 
Average Waiting Time: 3.333 
9 
7 
3 
4 
4 
2 
Sample 2: 
Input Format: 
Time Quantum: 3 
Number of Processes: 2 
Arrival Time, Needed Time P1: 0 2 
Arrival Time, Needed Time P1: 5 4 
Output Format: 
Queue updates:  
[ P1 ] 
[ Empty ] 
[ P2 ] 
[ P2 ] 
[ Empty ] 
Process 
P1 
P2 
Completion Time 
2 
9 
Average Waiting Time: 0.0 
Turnaround Time  
2 
4 
Waiting Time 
0 
0 
Helpful C++ Tips for This Problem 
● Struct Definition 
struct Process { 
int id; 
int arrival_time; 
int burst_time; 
int remaining_time; 
int completion_time; 
int turnaround_time; 
int waiting_time; 
}; 
● Tracking Time: Use a current_time variable that increments based on the 
time quantum or the remaining burst time of the process, whichever is smaller. 
● Precision: When calculating the Average Waiting Time, ensure you cast the 
sum to float or double to maintain decimal accuracy (e.g., 
(float)total_waiting_time / n).*/

class Process {
    private:
        // Attributes
        int id; //Unique identifier for the process (e.g., P1, P2, etc.)
        int arrival_time; //AT which the process arrives in the system
        int burst_time; //BT which is the total time needed for the process to finish
        int remaining_time; //RT which is the time left for the process to finish after some execution
        int completion_time; //CT which is the time at which the process finishes execution
        int turnaround_time; //TAT which is the total time taken by the process from arrival to completion
        //CT - AT
        int waiting_time; //WT which is the total time the process spends in the ready queue
        //TAT - BT

    public:
        Process(int id, int arrival_time, int burst_time) {
            this->id = id;
            this->arrival_time = arrival_time;
            this->burst_time = burst_time;
            remaining_time = burst_time;
            completion_time = 0;
            turnaround_time = 0;
            waiting_time = 0; 
        }

        // Getters
        int getId()             const { return id; }
        int getArrivalTime()    const { return arrival_time; }
        int getBurstTime()      const { return burst_time; }
        int getRemainingTime()  const { return remaining_time; }
        int getWaitingTime()    const { return waiting_time; }

        // Methods

        // Decrementing its total time needed
        void run(int run_time){
            remaining_time -= run_time;
        }

        // Check if process finished or not
        bool isFinished() const{
            return remaining_time == 0;
        }

        // Set completion time
        void setCompletionTime(int time){
            completion_time = time;
        }

        // Calc. TAT & WT
        void calculateStats(){
            turnaround_time = completion_time - arrival_time;
            waiting_time = turnaround_time - burst_time;
        }

        // Print results table
        void printStats() const{
            cout << "P" << id << "\t";
            cout << completion_time << "\t\t";
            cout << turnaround_time << "\t\t";
            cout << waiting_time << "\n";
        }

        // Comparing which one comes first 
        static bool compareArrivalTime(const Process& a, const Process& b){
            return a.arrival_time < b.arrival_time;
        }
};

// MergeSort Algorithm  //O(n log n)
void merge(vector<Process>& arr, int left, int mid, int right) {
    vector<Process> left_half(arr.begin() + left, arr.begin() + mid + 1);
    vector<Process> right_half(arr.begin() + mid + 1, arr.begin() + right + 1);
    int i = 0;        
    int j = 0;        
    int k = left;
    while(i < left_half.size() && j < right_half.size()){
        if(left_half[i].getArrivalTime() <= right_half[j].getArrivalTime()){
            arr[k] = left_half[i];
            i++;
        } else {
            arr[k] = right_half[j];
            j++;
        }
        k++;
    } 
    while(i < left_half.size()){
        arr[k] = left_half[i];
        i++;
        k++;
    }
    while(j < right_half.size()){
        arr[k] = right_half[j];
        j++;
        k++;
    }
}

void mergeSort(vector<Process>& arr, int left, int right){
    if(left >= right) return;
    int mid = (left + right) / 2;
    mergeSort(arr, left, mid);        
    mergeSort(arr, mid + 1, right);  
    merge(arr, left, mid, right);     
}

class RoundRobinScheduler {
    private:
        // Attributes
        int quantum;
        int current_time;
        int completed;
        vector<Process> processes;
        queue<int> ready_queue;
        vector<bool> in_queue;

        // printing queue stats
        void printQueue() const {
            queue<int> temp_queue = ready_queue;
            if(temp_queue.empty()){
                cout << "[ Empty ]" << endl;
                return;
            }
            cout << "[ ";
            while(!temp_queue.empty()){
                cout << "P" << processes[temp_queue.front()].getId();
                temp_queue.pop();
                if(!temp_queue.empty()) cout << ", ";
            }
            cout << " ]\n";
        }

        // add any process arrived up to the current_time to the ready queue
        void enqueueArrivals() { //O(n)
            for(int i = 0; i < processes.size(); i++){
                if(!in_queue[i] && processes[i].getArrivalTime() <= current_time){
                    ready_queue.push(i);
                    in_queue[i] = true;
                }
            }
        }

        // Directly jump to the process arrival time
        void jumpToNextArrival() {
            for(int i = 0; i < processes.size(); i++){
                if(!in_queue[i] && processes[i].getArrivalTime() > current_time){
                    current_time = processes[i].getArrivalTime();
                    ready_queue.push(i);
                    in_queue[i] = true;
                    break;
                }
            }
            printQueue();
        }

    public:
        RoundRobinScheduler(int quantum) {
            this->quantum = quantum;
            current_time = 0;
            completed = 0;
        }

        // Methods

        void addProcess(const Process& process) {
            processes.push_back(process);
        }

        // Sort process and Forming the Ready Queue
        void initialize() {
            mergeSort(processes, 0, processes.size() - 1);
            in_queue= vector<bool>(processes.size(), false);
            for(int i = 0; i < processes.size(); i++){
                if(processes[i].getArrivalTime() == 0){
                    ready_queue.push(i);
                    in_queue[i] = true;
                }
            }
            printQueue();
        }

        // Running the whole 
        void execute(){ //O(total CPU bursts) //O(n * max(BT)/quantum)
            while(!(ready_queue.empty()) || (completed != processes.size())){
                if(ready_queue.empty() && (completed != processes.size())) {
                    jumpToNextArrival();
                }
                int idx = ready_queue.front();
                ready_queue.pop();
                int run_time = min(quantum, processes[idx].getRemainingTime());
                current_time += run_time;
                processes[idx].run(run_time);
                enqueueArrivals();
                if(processes[idx].isFinished()){
                    processes[idx].setCompletionTime(current_time);
                    processes[idx].calculateStats();
                    completed++;
                }else{
                    ready_queue.push(idx);
                }
                printQueue();
            }
        }

        // Print the final output
        void printResults() const {
            int n = processes.size();
            int total_waiting_time = 0;
            cout << "\nProcess\tCompletion Time\tTurnaround Time\tWaiting Time\n";
            for(int i = 0; i < n; i++){
                processes[i].printStats();
                total_waiting_time += processes[i].getWaitingTime();
            }
            cout << fixed << setprecision(3);
            cout << "Average Waiting Time: " << (float)total_waiting_time / n << "\n";
        }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string c;
    int quantum, n;
    getline(cin, c, ':');
    cin >> quantum;
    getline(cin, c, ':');
    cin >> n;

    RoundRobinScheduler scheduler(quantum);
    for (int i = 1; i <= n; i++) {
        int arrival_time, burst_time;
        getline(cin, c, ':');
        cin >> arrival_time >> burst_time;
        scheduler.addProcess(Process(i, arrival_time, burst_time));
    }

    cout << "Queue updates:\n";
    scheduler.initialize();
    scheduler.execute();
    scheduler.printResults();
    return 0;
}

