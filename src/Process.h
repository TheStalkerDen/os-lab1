#pragma once
class Process
{
public: 
	enum ProcessType { Interactive, Background };

	Process(int id, ProcessType process_type, int input_time, int time_to_work, int& current_time) :
		real_working_time_(0),
		start_time_(-1),
		id_(id),
		input_time_(input_time),
		process_type_(process_type),
		time_to_work_(time_to_work),
		finished_time_(0),
		current_time_(current_time)
	{}

	void Work() {
		real_working_time_++; 
		if (start_time_ == -1) { start_time_ = current_time_; }
	}

	ProcessType GetProcessType() { return process_type_; }
	int GetWaitingTime() { return finished_time_ - start_time_ - real_working_time_ +1; }
	int GetRealWorkingTime() { return real_working_time_; }
	int GetStartTime() { return start_time_;}
	int GetId() { return id_; }
	int GetInputTime() { return input_time_; }
	int GetTimeToWork() { return time_to_work_; }
	int GetFinishedTime() { return finished_time_; }
	int GetFullTime() { return finished_time_ - start_time_ + 1; }
	bool IsProcessDone() { return time_to_work_ == real_working_time_; }
	void SetFinishdedTime() { finished_time_ = current_time_; }

private:
	
	const int id_;
	const int input_time_;
	const int time_to_work_;
	const ProcessType process_type_;

	int& current_time_;
	
	int finished_time_;
	int real_working_time_;
	int start_time_;
};

