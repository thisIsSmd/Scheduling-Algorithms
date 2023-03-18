/*

Code for CPU Scheduling Algorithms

Author:

Mohammed Mudasir Shaik

*/

#include<iostream>
#include<limits>
#include <algorithm> 
#include <iomanip>
#include <string.h> 


//Defining the functions used in the program
void fcfsAlgorithm();
void nonPreemptiveSJF();
void nonPreemptivePriority();
void preemptivePriority();
void roundRobin();
void SRJF();
int menu();

using namespace std;

class Process{ //Declaring all the variables used in all the function inside the Process class
    public:
		int pid;
        string processName;
        int arrivalTime;
		int arrival_time;
        int burstTime;
		int burst_time;
		int turnaround_time;
		int start_time;
		int completion_time;
		int remainingTime;
		int response_time;
        int responseTime;
        int completionTime;
        int waitingTime;
		int waiting_time;
		int priority;
        int turnAroundTime;
		bool isCompleted;
        
		void initialize()
		{
        	isCompleted = false;
			remainingTime = burstTime;
        }		
};

int numOfProcesses;

int main()
{	

	int selectOne = 0;
	selectOne = menu();
	
	while (selectOne != 7) // While loop to iterate the menu selection
	{				
		switch (selectOne)
		{
			case 1: cout << "\nYou selected FCFS Scheduling Algorithm from the Menu\n";
					fcfsAlgorithm();
					break;
			case 2: cout << "You selected Non-Preemptive SJF Scheduling Algorithm from the Menu\n";
					nonPreemptiveSJF();
					break;
			case 3: cout << "You selected Shortest Remaining Time First Scheduling Algorithm from the Menu\n";
					SRJF();
					break;
			case 4: cout << "You selected Non - Preemptive Priority Scheduling Algorithm from the Menu\n";
					nonPreemptivePriority();
					break;
			case 5: cout << "You selected Preemptive Priority Scheduling Algorithm from the Menu\n";
					preemptivePriority();
					break;
			case 6: cout << "You selected Round Robin Scheduling Algorithm from the Menu\n";
					roundRobin();
					break;
			default: cout<< "You have selected an invalid option \n";
					 break;			
		}
		selectOne = menu();
	}
	return 0;
}

//menu() function which contains the list of all CPU Alogorithms which asks user after every algorithm is executed
int menu() 
{
	int selectOne;
	
		cout << "Select any of the following scheduling algorithms:\n";
		cout << "1. First come First Server (FCFS) \n";
		cout << "2. Non-Preemptive Shortest-job-first (SJF)\n";
		cout << "3. Preemptive Shortest-job-first (SJF)\n";
		cout << "4. Non-Preemptive Priority Scheduling\n";
		cout << "5. Preemptive Priority Scheduling\n";
		cout << "6. Round Robin\n";
		cout << "7. exit\n";
		
		cin >> selectOne;

 return selectOne;
}

void preemptivePriority() //Function for Preemptive Priority
{
	int n;
    struct Process p[100];
    float avgTurnAroundTime;
    float avgWaitingTime;
    float avgResponseTime;
    float cpuUtilisation;
    int totalTurnaroundTime = 0;
    int totalWaitingTime = 0;
    int totalResponseTime = 0;
    int totalIdleTime = 0;
    float throughput;
    int burstRemaining[100];
    int isCompleted[100];
    memset(isCompleted,0,sizeof(isCompleted));

    cout << setprecision(2) << fixed;

    cout<<"Enter the number of processes: ";
    cin>>n;
	
	//Reading the Arrival Time, Burst Time and Priority of the process
    for(int i = 0; i < n; i++) {
        cout<<"Enter arrival time of process "<<i+1<<": ";
        cin>>p[i].arrival_time;
        cout<<"Enter burst time of process "<<i+1<<": ";
        cin>>p[i].burst_time;
        cout<<"Enter priority of the process "<<i+1<<": ";
        cin>>p[i].priority;
        p[i].pid = i+1;
        burstRemaining[i] = p[i].burst_time;
        cout<<endl;
    }

    int currentTime = 0;
    int completed = 0;
    int prev = 0;

    while(completed != n) {
        int idx = -1;
        int mx = -1;
        for(int i = 0; i < n; i++) {
            if(p[i].arrival_time <= currentTime && isCompleted[i] == 0) {
                if(p[i].priority > mx) {
                    mx = p[i].priority;
                    idx = i;
                }
                if(p[i].priority == mx) {
                    if(p[i].arrival_time < p[idx].arrival_time) {
                        mx = p[i].priority;
                        idx = i;
                    }
                }
            }
        }


        if(idx != -1) {
            if(burstRemaining[idx] == p[idx].burst_time) {
                p[idx].start_time = currentTime;
                totalIdleTime += p[idx].start_time - prev;
            }
            burstRemaining[idx] -= 1;
            currentTime++;
            prev = currentTime;
            
            if(burstRemaining[idx] == 0) {
                p[idx].completion_time = currentTime;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                p[idx].response_time = p[idx].start_time - p[idx].arrival_time;


                totalTurnaroundTime += p[idx].turnaround_time;
                totalWaitingTime += p[idx].waiting_time;
                totalResponseTime += p[idx].response_time;


                isCompleted[idx] = 1;
                completed++;
            }
        }
        else {
             currentTime++;
        }  
    }


    int minArrivalTime = 10000000;
    int maxCompletionTime = -1;
    for(int i = 0; i < n; i++) {
        minArrivalTime = min(minArrivalTime,p[i].arrival_time);
        maxCompletionTime = max(maxCompletionTime,p[i].completion_time);
    }

    avgTurnAroundTime = (float) totalTurnaroundTime / n; //Calculating the Average Turn around time
    avgWaitingTime = (float) totalWaitingTime / n; //Calculating average waitingTime
    avgResponseTime = (float) totalResponseTime / n; //Calculating average responseTime
    cpuUtilisation = ((maxCompletionTime - totalIdleTime) / (float) maxCompletionTime )*100; //Calculating CPU Utilization
    throughput = float(n) / (maxCompletionTime - minArrivalTime); //Calculating Throughput
 
    cout<<endl<<endl;

    cout<<"#P\t"<<"AT\t"<<"BT\t"<<"PRI\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"RT\t"<<"\n"<<endl;
	
	//Displaying the Average Turnaround time, Average Waiting Time, Average Response Time, CPU Uitilization and Throughput
    for(int i = 0; i < n; i++) {
        cout<<p[i].pid<<"\t"<<p[i].arrival_time<<"\t"<<p[i].burst_time<<"\t"<<p[i].priority<<"\t"<<p[i].start_time<<"\t"<<p[i].completion_time<<"\t"<<p[i].turnaround_time<<"\t"<<p[i].waiting_time<<"\t"<<p[i].response_time<<"\t"<<"\n"<<endl;
    }
    cout<<"Average Turnaround Time = "<<avgTurnAroundTime<<endl;
    cout<<"Average Waiting Time = "<<avgWaitingTime<<endl;
    cout<<"Average Response Time = "<<avgResponseTime<<endl;
    cout<<"CPU Utilization = "<<cpuUtilisation<<"%"<<endl;
    cout<<"Throughput = "<<throughput<<" process/unit time"<<endl;

}
void roundRobin() //Function for Round Robin Scheduling Algorithm
{
    int timeQuantum;
    int currentTime = 0;

    cout << "\nEnter Time Quantum: ";
    cin >> timeQuantum;

    cout << "\nEnter no. of processes: ";
    cin >> numOfProcesses;

    Process processes[numOfProcesses];
	
	//Reading the Arrival Time, Burst Time and Priority of the process
    for(int n=0;n<numOfProcesses;n++)
	{
        cout << "Enter Process Name for " << (n+1) << ": ";
        cin >> processes[n].processName;
        cout << "Enter Arrival Time for Process " << (n+1) << ": ";
        cin >> processes[n].arrivalTime;
        cout << "Enter Burst Time for Process " << (n+1) << ": ";
        cin >> processes[n].burstTime;
        processes[n].initialize();
    }

    cout << "\n" << endl;

    currentTime = processes[0].arrivalTime;
    int remainingProcesses = numOfProcesses;

    for(int i=0;i<numOfProcesses;i=(i+1)%numOfProcesses)
	{
        if(processes[i].remainingTime > 0 && processes[i].arrivalTime <= currentTime)
		{
        	if(processes[i].remainingTime == processes[i].burstTime)
			{
        		processes[i].responseTime = currentTime;
        	}

        	if(processes[i].remainingTime <= timeQuantum)
			{
        		currentTime += processes[i].remainingTime;
        		processes[i].completionTime = currentTime;
        		processes[i].remainingTime = 0;
                remainingProcesses--;
        	}
        	else
			{
        		currentTime += timeQuantum;
        		processes[i].remainingTime -= timeQuantum;
        	}
        }

        if(remainingProcesses == 0)
		{
            break;
        }
    }

    int sumResponseTime = 0;
    int sumCompletionTime = 0;
    int sumWaitingTime = 0;
    int sumTurnAroundTime = 0;
	
	//Displaying the Average Turnaround time, Average Waiting Time, Average Response Time, CPU Uitilization and Throughput
    for(int n=0;n<numOfProcesses;n++)
	{
        cout << "\nProcess " << processes[n].processName << ":\n";
        cout << "Response Time: " << processes[n].responseTime << endl;
        cout << "Completion Time: " << processes[n].completionTime << endl;
        processes[n].turnAroundTime = processes[n].completionTime - processes[n].arrivalTime;
        processes[n].waitingTime = processes[n].turnAroundTime - processes[n].burstTime;
        cout << "Waiting Time: " << processes[n].waitingTime << endl;
        cout << "Turn Around Time: " << processes[n].turnAroundTime << "\n" << endl;

        sumResponseTime += processes[n].responseTime;
        sumCompletionTime += processes[n].completionTime;
        sumWaitingTime += processes[n].waitingTime;
        sumTurnAroundTime += processes[n].turnAroundTime;
    }

	cout << "\n\nAverage Response Time for " << (numOfProcesses) << " Processes: " << (float) sumResponseTime/numOfProcesses;
	cout << "\n\nAverage Completion Time for " << (numOfProcesses) << " Processes: " << (float) sumCompletionTime/numOfProcesses;
    cout << "\n\nAverage Waiting Time for " << (numOfProcesses) << " Processes: " << (float) sumWaitingTime/numOfProcesses;
    cout << "\n\nAverage Turn Around Time for " << (numOfProcesses) << " Processes: " << (float) sumTurnAroundTime/numOfProcesses;
}

void nonPreemptivePriority() // Function Non Preemptive Priority
{
	
    cout << "Enter no. of processes: ";
    cin >> numOfProcesses;

    Process processes[numOfProcesses];
	
	//Displaying the Average Turnaround time, Average Waiting Time, Average Response Time, CPU Uitilization and Throughput
    for(int n=0;n<numOfProcesses;n++)
	{
        cout << "\nEnter Process Name for " << (n+1) << ": ";
        cin >> processes[n].processName;
        cout << "Enter Arrival Time for Process " << (n+1) << ": ";
        cin >> processes[n].arrivalTime;
        cout << "Enter Burst Time for Process " << (n+1) << ": ";
        cin >> processes[n].burstTime;
        cout << "Enter Priority for Process " << (n+1) << ": ";
        cin >> processes[n].priority;

        processes[n].initialize();
    }
	
    cout << "\n" << endl;

    for(int i=0;i<numOfProcesses-1;i++)
	{
        for(int j=i+1;j<numOfProcesses;j++)
		{
            if(processes[j].arrivalTime < processes[i].arrivalTime)
			{
                Process temp = processes[j];
                processes[j] = processes[i];
                processes[i] = temp;
            }
        }
    }

    int currentTime = 0;

    while(true)
	{
    	int currentHighestPriorityIndex = -1;
    	int currentHighestPriority = numeric_limits<int>::max();

    	bool isAllCompleted = true;

    	for(int i=0;i<numOfProcesses;i++)
		{
    		if(processes[i].remainingTime > 0)
			{
    			isAllCompleted = false;
                if(processes[i].arrivalTime <= currentTime)
				{
                    if(processes[i].priority < currentHighestPriority)
					{
                        currentHighestPriority = processes[i].priority;
                        currentHighestPriorityIndex = i;
                    }
                }
    		}
    	}

    	if(isAllCompleted)
		{
    		break;
    	}
        		
		processes[currentHighestPriorityIndex].responseTime = currentTime;
        processes[currentHighestPriorityIndex].remainingTime = 0;
        currentTime += processes[currentHighestPriorityIndex].burstTime;
        processes[currentHighestPriorityIndex].completionTime = currentTime; 	
    }

    int sumResponseTime = 0;
    int sumCompletionTime = 0;
    int sumWaitingTime = 0;
    int sumTurnAroundTime = 0;
	
	//Displaying the Average Turnaround time, Average Waiting Time, Average Response Time, CPU Uitilization and Throughput
    for(int n=0;n<numOfProcesses;n++)
	{
        cout << "\nProcess " << processes[n].processName << ":\n";
        cout << "Response Time: " << processes[n].responseTime << endl;
        cout << "Completion Time: " << processes[n].completionTime << endl;
        processes[n].turnAroundTime = processes[n].completionTime - processes[n].arrivalTime;
        processes[n].waitingTime = processes[n].turnAroundTime - processes[n].burstTime;
        cout << "Waiting Time: " << processes[n].waitingTime << endl;
        cout << "Turn Around Time: " << processes[n].turnAroundTime << "\n" << endl;

        sumResponseTime += processes[n].responseTime;
        sumCompletionTime += processes[n].completionTime;
        sumWaitingTime += processes[n].waitingTime;
        sumTurnAroundTime += processes[n].turnAroundTime;
    }

	cout << "\n\nAverage Response Time for " << (numOfProcesses) << " Processes: " << (float) sumResponseTime/numOfProcesses;
	cout << "\n\nAverage Completion Time for " << (numOfProcesses) << " Processes: " << (float) sumCompletionTime/numOfProcesses;
    cout << "\n\nAverage Waiting Time for " << (numOfProcesses) << " Processes: " << (float) sumWaitingTime/numOfProcesses;
    cout << "\n\nAverage Turn Around Time for " << (numOfProcesses) << " Processes: " << (float) sumTurnAroundTime/numOfProcesses;
	
}

void SRJF() //Function ofr SRJF
{
	    cout << "Enter no. of processes: ";
	    cin >> numOfProcesses;

	    Process processes[numOfProcesses];

	    for(int n=0;n<numOfProcesses;n++)
		{
	        cout << "\nEnter Process Name for " << (n+1) << ": ";
	        cin >> processes[n].processName;
	        cout << "Enter Arrival Time for Process " << (n+1) << ": ";
	        cin >> processes[n].arrivalTime;
	        cout << "Enter Burst Time for Process " << (n+1) << ": ";
	        cin >> processes[n].burstTime;
	
	        processes[n].initialize();
	    }

	    cout << "\n" << endl;

	    for(int i=0;i<numOfProcesses-1;i++)
		{
	        for(int j=i+1;j<numOfProcesses;j++)
			{
	            if(processes[j].arrivalTime < processes[i].arrivalTime)
				{
	                Process temp = processes[j];
	                processes[j] = processes[i];
	                processes[i] = temp;
	            }
	        }
	    }
	
	    int currentTime = 0;

	    while(true)
		{
	    	int currentShortestJobIndex = -1;
	    	int currentShortestJobRemainingTime = numeric_limits<int>::max();
	
	    	bool isAllCompleted = true;

	    	for(int i=0;i<numOfProcesses;i++)
			{
	    		if(processes[i].remainingTime > 0)
				{
	    			isAllCompleted = false;
	                if(processes[i].arrivalTime <= currentTime)
					{
	                    if(processes[i].remainingTime < currentShortestJobRemainingTime)
						{
	                        currentShortestJobRemainingTime = processes[i].remainingTime;
	                        currentShortestJobIndex = i;
	                    }
	                }
	    		}
	    	}
	
	    	if(isAllCompleted)
			{
	    		break;
	    	}

			if(processes[currentShortestJobIndex].remainingTime == processes[currentShortestJobIndex].burstTime)
			{
				processes[currentShortestJobIndex].responseTime = currentTime;
			}
	
	    	processes[currentShortestJobIndex].remainingTime--;
	        currentTime++;
	    	
			if(processes[currentShortestJobIndex].remainingTime == 0)
			{
				processes[currentShortestJobIndex].completionTime = currentTime;
			}
	    }

	    int sumResponseTime = 0;
	    int sumCompletionTime = 0;
	    int sumWaitingTime = 0;
	    int sumTurnAroundTime = 0;
	
		
		//Displaying the Average Turnaround time, Average Waiting Time, Average Response Time, CPU Uitilization and Throughput
	    for(int n=0;n<numOfProcesses;n++)
		{
	        cout << "\nProcess " << processes[n].processName << ":\n";
	        cout << "Response Time: " << processes[n].responseTime << endl;
	        cout << "Completion Time: " << processes[n].completionTime << endl;
	        processes[n].turnAroundTime = processes[n].completionTime - processes[n].arrivalTime;
	        processes[n].waitingTime = processes[n].turnAroundTime - processes[n].burstTime;
	        cout << "Waiting Time: " << processes[n].waitingTime << endl;
	        cout << "Turn Around Time: " << processes[n].turnAroundTime << "\n" << endl;

	        sumResponseTime += processes[n].responseTime;
	        sumCompletionTime += processes[n].completionTime;
	        sumWaitingTime += processes[n].waitingTime;
	        sumTurnAroundTime += processes[n].turnAroundTime;
	    }

		cout << "\n\nAverage Response Time for " << (numOfProcesses) << " Processes: " << (float) sumResponseTime/numOfProcesses;
		cout << "\n\nAverage Completion Time for " << (numOfProcesses) << " Processes: " << (float) sumCompletionTime/numOfProcesses;
	    cout << "\n\nAverage Waiting Time for " << (numOfProcesses) << " Processes: " << (float) sumWaitingTime/numOfProcesses;
	    cout << "\n\nAverage Turn Around Time for " << (numOfProcesses) << " Processes: " << (float) sumTurnAroundTime/numOfProcesses;
}

void nonPreemptiveSJF() // Function for Non Preemptive SJF
{
    
	cout << "Enter no. of processes: ";
    cin >> numOfProcesses;

    Process processes[numOfProcesses];

    for(int n=0;n<numOfProcesses;n++)
	{
        cout << "\nEnter Process Name for " << (n+1) << ": ";
        cin >> processes[n].processName;
        cout << "Enter Arrival Time for Process " << (n+1) << ": ";
        cin >> processes[n].arrivalTime;
        cout << "Enter Burst Time for Process " << (n+1) << ": ";
        cin >> processes[n].burstTime;

        processes[n].initialize();
    }

    cout << "\n" << endl;

    for(int i=0;i<numOfProcesses-1;i++)
	{
        for(int j=i+1;j<numOfProcesses;j++)
		{
            if(processes[j].arrivalTime < processes[i].arrivalTime)
			{
                Process temp = processes[j];
                processes[j] = processes[i];
                processes[i] = temp;
            }
        }
    }

    int currentTime = 0;
	
    while(true)
	{
    	int currentShortestJobIndex = -1;
    	int currentShortestJobRemainingTime = numeric_limits<int>::max();

    	bool isAllCompleted = true;

    	for(int i=0;i<numOfProcesses;i++)
		{
    		if(!processes[i].isCompleted)
			{
    			isAllCompleted = false;
                if(processes[i].arrivalTime <= currentTime)
				{
                    if(processes[i].burstTime < currentShortestJobRemainingTime)
					{
                        currentShortestJobRemainingTime = processes[i].burstTime;
                        currentShortestJobIndex = i;
    			    }
                }

    		}
    	}

    	if(isAllCompleted)
		{
    		break;
    	}

		processes[currentShortestJobIndex].responseTime = currentTime;

        currentTime += processes[currentShortestJobIndex].burstTime;
    	processes[currentShortestJobIndex].isCompleted = true;

        processes[currentShortestJobIndex].completionTime = currentTime;    	
    }

    int sumResponseTime = 0;
    int sumCompletionTime = 0;
    int sumWaitingTime = 0;
    int sumTurnAroundTime = 0;

	
	//Displaying the Average Turnaround time, Average Waiting Time, Average Response Time, CPU Uitilization and Throughput
    for(int n=0;n<numOfProcesses;n++)
	{
        cout << "\nProcess " << processes[n].processName << ":\n";
        cout << "Response Time: " << processes[n].responseTime << endl;
        cout << "Completion Time: " << processes[n].completionTime << endl;
        processes[n].turnAroundTime = processes[n].completionTime - processes[n].arrivalTime;
        processes[n].waitingTime = processes[n].turnAroundTime - processes[n].burstTime;
        cout << "Waiting Time: " << processes[n].waitingTime << endl;
        cout << "Turn Around Time: " << processes[n].turnAroundTime << "\n" << endl;

        sumResponseTime += processes[n].responseTime;
        sumCompletionTime += processes[n].completionTime;
        sumWaitingTime += processes[n].waitingTime;
        sumTurnAroundTime += processes[n].turnAroundTime;
    }

	cout << "\n\nAverage Response Time for " << (numOfProcesses) << " Processes: " << (float) sumResponseTime/numOfProcesses;
	cout << "\n\nAverage Completion Time for " << (numOfProcesses) << " Processes: " << (float) sumCompletionTime/numOfProcesses;
    cout << "\n\nAverage Waiting Time for " << (numOfProcesses) << " Processes: " << (float) sumWaitingTime/numOfProcesses;
    cout << "\n\nAverage Turn Around Time for " << (numOfProcesses) << " Processes: " << (float) sumTurnAroundTime/numOfProcesses;
}

void fcfsAlgorithm() //Function for FCFS Algorithm
{
    cout << "Enter no. of processes: ";
    cin >> numOfProcesses;

    Process processes[numOfProcesses];

    for(int n=0; n < numOfProcesses; n++)
	{
        cout << "\nEnter Process Name for " << (n+1) << ": ";
        cin >> processes[n].processName;
        cout << "Enter Arrival Time for Process " << (n+1) << ": ";
        cin >> processes[n].arrivalTime;
        cout << "Enter Burst Time for Process " << (n+1) << ": ";
        cin >> processes[n].burstTime;
    }

    cout << "\n" << endl;

    for(int i=0; i < numOfProcesses-1; i++)
	{
        for(int j=i+1;j<numOfProcesses;j++)
		{
            if(processes[j].arrivalTime < processes[i].arrivalTime)
			{
                Process temp = processes[j];
                processes[j] = processes[i];
                processes[i] = temp;
            }
        }
    }

    int sumResponseTime = 0;
    int sumCompletionTime = 0;
    int sumWaitingTime = 0;
    int sumTurnAroundTime = 0;
	int cumulativeSum = 0;
	
	//Displaying the Average Turnaround time, Average Waiting Time, Average Response Time, CPU Uitilization and Throughput
    for(int n=0; n < numOfProcesses; n++)
	{
        processes[n].waitingTime = cumulativeSum;
        processes[n].completionTime =  processes[n].waitingTime + processes[n].burstTime;
        if(n == 0)
		{
            processes[n].responseTime = 0;
        }
        else
		{
            processes[n].responseTime = processes[n-1].completionTime;
        }
        
        processes[n].turnAroundTime = processes[n].completionTime - processes[n].arrivalTime;

        cout << "\nProcess " << processes[n].processName << ":\n";
        cout << "Response Time: " << processes[n].responseTime << endl;
        cout << "Completion Time: " << processes[n].completionTime << endl;
        cout << "Waiting Time: " << processes[n].waitingTime << endl;
        cout << "Turn Around Time: " << processes[n].turnAroundTime << endl;

        sumResponseTime += processes[n].responseTime;
        sumCompletionTime += processes[n].completionTime;
        sumWaitingTime += processes[n].waitingTime;
        sumTurnAroundTime += processes[n].turnAroundTime;

        cumulativeSum += processes[n].burstTime;
    }
	
    cout << "\n\nAverage Response Time for " << (numOfProcesses) << " Processes: " << (float) sumResponseTime/numOfProcesses;
    cout << "\n\nAverage Completion Time for " << (numOfProcesses) << " Processes: " << (float) sumCompletionTime/numOfProcesses;
    cout << "\n\nAverage Waiting Time for " << (numOfProcesses) << " Processes: " << (float) sumWaitingTime/numOfProcesses;
    cout << "\n\nAverage Turn Around Time for " << (numOfProcesses) << " Processes: " << (float) sumTurnAroundTime/numOfProcesses;
}
