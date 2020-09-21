#include "SJF.h"

#include <algorithm>
#include <iostream>

void SJF::AddProcess(Process* process)
{
	background_processes_.push_back(process);
}

void SJF::DoSJF()
{
	
	if (current_background_process_ != nullptr) {
		DoCurrentProcess();
	}
	else {
		if (!IsProcessVectorEmpty()) {
			SetCurrentProcessFromVector();
			DoCurrentProcess();
		}
		else {
			std::cout << "Background process vector is empty. No process is working now\n";
		}
		
	}
}

void SJF::DoCurrentProcess()
{
	std::cout << "Now is working background process with id " << current_background_process_->GetId() << "\n";
	current_background_process_->Work();
	if (IsCurrentProcessDone()) {
		process_ended_counter_++;
		std::cout << "Process has ended job\n";
		current_background_process_->SetFinishdedTime();
		current_background_process_ = nullptr;
	}
}

void SJF::SetCurrentProcessFromVector()
{
	SortProcesses();
	current_background_process_ = background_processes_.back();
	background_processes_.pop_back();
}

bool SJF::IsProcessVectorEmpty()
{
	return background_processes_.empty();
}

bool SJF::IsCurrentProcessDone()
{
	return current_background_process_->IsProcessDone();
}

void SJF::SortProcesses()
{
	std::sort(background_processes_.begin(), background_processes_.end(), [](Process* process1, Process* process2) {
		return process1->GetTimeToWork() > process2->GetTimeToWork();
		});
}

