#include<iostream>
#include<vector>
#include<iomanip>

using namespace std;
class Process {
public:
int id, at, bt, ct, tat, wt, rt, priority;
void completed(int time) {
ct = time;
tat = ct - at;
wt = tat - bt;
}
};
void sortByArrivalTime(vector<Process>& procs) {
int n = procs.size();
for (int i=0; i<n; i++) {
    for (int j=0; j<n-i-1; j++) {
    if (procs[j].at > procs[j+1].at) {
        swap(procs[j], procs[j+1]);
    }
    }
}
}
void printProc(Process& p) {
cout << setw(4) << "P"<<p.id;
cout << setw(5) << p.at;
cout << setw(5) << p.bt;
cout << setw(5) << p.priority;
cout << setw(5) << p.wt;
cout << setw(5) << p.tat;
}
int main() {
int n, tq;
cout << "Enter number of processes: ";
cin >> n;
cout << "Enter time quantum: ";
cin >> tq;
vector<Process> procs(n);
vector<Process> q1, q2;
for (int i=0; i<n; i++) {
    int id, at, bt, priority;
    cin >> id >> at >> bt >> priority;
    procs[i].id = id;
    procs[i].at = at;
    procs[i].bt = bt;
    procs[i].rt = bt;
    procs[i].priority = priority;
}
sortByArrivalTime(procs);
int curProcInd = 0;
int qInd1 = -1;
int time = 0;
int done = 0;
while (q1.size() > 0 || q2.size() > 0 || curProcInd < n) {
    while (curProcInd < n && procs[curProcInd].at <= time) {
        if (procs[curProcInd].priority == 1) {
        q1.push_back(procs[curProcInd++]);
        } 
        else {
        q2.push_back(procs[curProcInd++]);
        }
    }
    if (q1.size() > 0) {
    qInd1 = (qInd1 + 1) % q1.size();
    int burst = min(q1[qInd1].rt, tq);
    time += burst;
    q1[qInd1].rt -= burst;
    cout << "P" << q1[qInd1].id;
    if (q1[qInd1].rt <= 0) {
    q1[qInd1].completed(time);
    done++;
    for (int i=0; i<n; i++) {
        if (procs[i].id == q1[qInd1].id) {
            procs[i] = q1[qInd1];
        }
    }
    q1.erase(q1.begin() + qInd1);
}
if (done < n) cout << "->";
} else if (q2.size() > 0) {
    // Non-preemptive SJF: pick the process in q2 with smallest remaining time (rt)
    int minIdx = 0;
    for (int k = 1; k < (int)q2.size(); ++k) {
        if (q2[k].rt < q2[minIdx].rt) minIdx = k;
    }
    int burst = q2[minIdx].rt;            // run to completion
    time += burst;
    q2[minIdx].rt -= burst;
    cout << "P" << q2[minIdx].id;         // print the chosen process id
    if (q2[minIdx].rt <= 0) {
    q2[minIdx].completed(time);
    done++;
    for (int i=0; i<n; i++) {
    if (procs[i].id == q2[minIdx].id) {
    procs[i] = q2[minIdx];
    }
    }
    q2.erase(q2.begin() + minIdx);
    }
if (done < n) cout << "->";
} else time++;

}
cout<< endl;
cout<< "--------------------------------" << endl;
cout<< setw(5) << "ID";
cout<< setw(5) << "AT";
cout<< setw(5) << "BT";
cout<< setw(5) << "Pr";
cout<< setw(5) << "WT";
cout<< setw(5) << "TAT";
cout<< endl;
int totalWT = 0, totalTAT = 0;

for (int i=0; i<n; i++) {
printProc(procs[i]);
totalWT += procs[i].wt;
totalTAT += procs[i].tat;
cout << endl;
}
cout<<"--------------------------------" << endl;
cout<<"Average Waiting Time: " << (float)totalWT/n << endl;
cout<<"Average Turnaround Time: " << (float)totalTAT/n <<endl;
cout<<endl;
return 0;
}