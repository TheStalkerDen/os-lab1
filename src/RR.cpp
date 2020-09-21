#include "RR.h"
#include <iostream>

void RR::DoRR()
{
	if (current_interactive_process_ != nullptr) {
		DoCurrentProcess();
	}
	else {
		if (!IsProcessQueueEmpty()) {
			SetCurrentProcessFromQueue();
			DoCurrentProcess();
		}
		else {
			std::cout << "Interactive process queue is empty. No process is working\n";
		}
	}
	IncreaseModuleTime();
}

void RR::AddProcess(Process* process)
{
	interactive_processes_.push(process);
}

bool RR::IsProcessQueueEmpty()
{
	return interactive_processes_.empty();
}

bool RR::IsCurrentProcessEnded()
{
	return current_interactive_process_->IsProcessDone();
}

bool RR::IsEndOfQwant()
{
	return module_time_ == rr_qwant_ - 1;
}

void RR::SetCurrentProcessFromQueue()
{
	current_interactive_process_ = interactive_processes_.front();
	interactive_processes_.pop();
}

void RR::IncreaseModuleTime()
{
	module_time_ = (module_time_ + 1) % rr_qwant_;
}

void RR::DoCurrentProcess()
{
	std::cout << "Now is working interacive process with id " << current_interactive_process_->GetId() << "\n";
	current_interactive_process_->Work();
	if (IsCurrentProcessEnded()) {
		process_ended_counter_++;
		std::cout << "This process has ended his job\n";
		module_time_ = -1;
		current_interactive_process_->SetFinishdedTime();
		current_interactive_process_ = nullptr;
	}
	else {
		std::cout << "Process has worked " << current_interactive_process_->GetRealWorkingTime() << "\n";
		if (IsEndOfQwant()) {
			std::cout << "Now is end of time quark\n";
			AddProcess(current_interactive_process_);
			current_interactive_process_ = nullptr;
		}
	}
}
