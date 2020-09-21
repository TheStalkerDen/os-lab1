#pragma once

#include "Process.h"
#include <queue>

class RR
{

public:

	RR(int& process_ended_counter, int rr_qwant) :
		module_time_(0),
		rr_qwant_(rr_qwant),
		process_ended_counter_(process_ended_counter),
		current_interactive_process_(nullptr)
	{}

	void DoRR();

	void AddProcess(Process* process);


private:

	bool IsProcessQueueEmpty();
	bool IsCurrentProcessEnded();
	bool IsEndOfQwant();
	void SetCurrentProcessFromQueue();
	void IncreaseModuleTime();

	void DoCurrentProcess();
	

	int& process_ended_counter_;

	Process* current_interactive_process_;
	std::queue<Process*> interactive_processes_ = {};
	int rr_qwant_;
	int module_time_;

};

