#pragma once

#include <vector>

#include "Process.h"

class SJF
{

public:

	SJF(int& process_ended_counter):
		process_ended_counter_(process_ended_counter),
		current_background_process_(nullptr)
	{}
	
	void AddProcess(Process* process);

	void DoSJF();
		

private:

	void DoCurrentProcess();

	void SetCurrentProcessFromVector();
	bool IsProcessVectorEmpty();
	bool IsCurrentProcessDone();
	void SortProcesses();

	int& process_ended_counter_;

	std::vector<Process*> background_processes_ = {};
	Process* current_background_process_;

};

