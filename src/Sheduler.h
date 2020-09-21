#pragma once

#include <vector>
#include "Process.h"


class Sheduler
{
public:
	Sheduler(): 
		current_time_(0),
		module_time_(0),
		time_for_interactive_process_(8),
		time_for_background_process_(2),
		rr_qwant_(4),
		process_counter_(0),
		process_ended_counter_(0)
	{}

	void Start();

private:

	void InitiateProcessList();
	void InitiateProcessListByRandom();
	void InitiateProcessListFromFile();
	void PrintInfoTable();

	void IncreaseTime();
    std::vector<Process*> GetCurrentInputProcesses();

	int module_time_;

	int current_time_;
	int process_counter_;
	int process_ended_counter_;

	std::vector<Process> processes_;
	std::vector<Process*> background_processes_;

	int time_for_interactive_process_;
	int time_for_background_process_;
	int rr_qwant_;
};

