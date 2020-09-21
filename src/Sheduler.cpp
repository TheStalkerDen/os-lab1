#include <map>
#include <iostream>
#include <algorithm>
#include <list>
#include <fstream>
#include <sstream>

#include "Sheduler.h"
#include "Debug.h"
#include "RR.h"
#include "SJF.h"
#include "TableForPrint.h"
#include "imatch.h"

using namespace std;

enum Choice { FromFile=2, ByRandom=1 };

void Sheduler::Start() {
    InitiateProcessList();
	RR rr = RR(process_ended_counter_,rr_qwant_);
	SJF sjf = SJF(process_ended_counter_);
	while (true) {
		
		vector<Process*> input_processes = GetCurrentInputProcesses();
		for (Process* input_process : input_processes) {
			if (input_process) {
				// New process coming
				if (input_process->GetProcessType() == Process::ProcessType::Interactive) {
					rr.AddProcess(input_process);
					PRINT("I am interactive");
				}
				else {
					sjf.AddProcess(input_process);
					PRINT("I am background");
				}
			}
		}
		
		cout << "--------------------------------\n";
		cout << "Time: " << current_time_ << "\n";
		cout << "ModuleTime: " << module_time_ << "\n";
		if (module_time_ < time_for_interactive_process_) {
			rr.DoRR(); //RR algo
		}
		else {
			sjf.DoSJF(); // SJF algo
		}
		
		cout << "---------------------------------\n";

		DEBUG_PRINT_VAR(current_time_);
		DEBUG_PRINT_VAR(process_ended_counter_);
		if (process_ended_counter_ == process_counter_) {
			break;
		}

		IncreaseTime();
	}
    PrintInfoTable();

}

void Sheduler::IncreaseTime() {
	current_time_++;
	module_time_ = (module_time_ + 1) % (time_for_background_process_ + time_for_interactive_process_);
}

std::vector<Process*> Sheduler::GetCurrentInputProcesses()
{
	vector<Process*> input_processes{};
	for (Process& process : processes_) {
		if (process.GetInputTime() == current_time_) {
			input_processes.push_back(&process);
		}
	}
	return input_processes;
}

void Sheduler::InitiateProcessList() {
	cout << "How do you want to generate list of processes: (default is By Random)\n";
	cout << "1) By random\n";
	cout << "2) Read from file\n";

	int choice;
	cin >> choice;
	switch (choice)
	{
	case FromFile:
		InitiateProcessListFromFile();
		break;
	case ByRandom:
	default:
		InitiateProcessListByRandom();
		break;
	}
}

void Sheduler::InitiateProcessListByRandom() {
	cout << "How many process to create (default is 8): ";
	cin >> process_counter_;
	if (process_counter_ < 1) {
		process_counter_ = 8;
	}
   
	/* Sorry for nonchecking input*/
	cout << "Time for interactive process (recommend is 8): ";
	cin >> time_for_interactive_process_;
	cout << "Qwant for RR (default is 4): ";
	cin >> rr_qwant_;
	cout << "Time for background process (recommend is 2): ";
	cin >> time_for_background_process_;
	
	for (int i = 0; i < process_counter_; i++) {
		Process::ProcessType type = (rand() % 2 == 0) ? Process::ProcessType::Interactive : Process::Process::Background;
	    processes_.push_back(Process(i, type, i + rand() % 2, rand() % 4 + 1, current_time_));
	}
}

void Sheduler::InitiateProcessListFromFile() {
	ifstream input_file = ifstream("input.txt");
	if (input_file.is_open()) {
		std::string line;
		int line_count = 0;
		while (getline(input_file, line)) {
			std::istringstream ss(line);
			switch (line_count) {
				case 0:
					ss >> imatch("interactive_time") >> imatch("=") >> time_for_interactive_process_; break;
				case 1:
					ss >> imatch("background_time") >> imatch("=") >> time_for_background_process_; break;
				case 2:
					ss >> imatch("rr_qwant") >> imatch("=") >> rr_qwant_; break;
				default:
				{
					int id;
					ss >> id;
					char process_type;
					ss >> process_type;
					int input_time;
					ss >> input_time;
					int work_time;
					ss >> work_time;
					Process::ProcessType type;
					switch (process_type) {
						case 'i': type = Process::ProcessType::Interactive; break;
						case 'b': type = Process::ProcessType::Background; break;
						default: cerr << "Incorrect value of type for process"; exit(EXIT_FAILURE); break;
					}
					processes_.push_back(Process(id, type, input_time, work_time, current_time_));
					process_counter_++;
					break;
				}
			}
			line_count++;
		}
	}
	else {
		cout << "Can't open input.txt\n";
		exit(EXIT_FAILURE);
	}
	input_file.close();
}

void Sheduler::PrintInfoTable() {

	int all_waiting_time = 0;
	int all_execute_time_with_waiting = 0;

	cout << "Time for interactive process: " << time_for_interactive_process_ << "\n";
	cout << "Time for background process: " << time_for_background_process_ << "\n";
	cout << "Qwant for RR: " << rr_qwant_;

	cout << "\n\nProcess" << "| Type " <<  "| Appear time " << "| Working time " << "| Started time " << "| Waiting time" << "| Finished time " << "| Full time |" << endl;
	for (auto& process : processes_) {
		char processType = process.GetProcessType() == Process::ProcessType::Interactive ? 'i' : 'b';
		printTableElement(process.GetId(),7);
		printTableElement(processType, 6);
		printTableElement(process.GetInputTime(), 13);
		printTableElement(process.GetRealWorkingTime(), 14);
		printTableElement(process.GetStartTime(), 14);
		printTableElement(process.GetWaitingTime(), 13);
		printTableElement(process.GetFinishedTime(),15);
		printTableElement(process.GetFullTime(), 11);
		cout << endl;
		all_waiting_time += process.GetWaitingTime();
		all_execute_time_with_waiting += process.GetFullTime();
	}
	
	cout << "Average waitining: " << all_waiting_time / (double)process_counter_ << "\n";
	cout << "Averege execute time with waiting: " << all_execute_time_with_waiting / (double)process_counter_ << "\n";
}