#pragma once

#include <string>
#include <thread>
#include <memory>
#include <atomic>
#include <mutex>

#include "ThreadPool.h"
#include "ThreadRAII.h"
#include "ThreadRunner.h"

class ThreadPool;

class ThreadControl
{
public:
	explicit ThreadControl(std::shared_ptr<ThreadRunner> runner);

	void Start();
	void Done();
	void Awake();
	void Stop();

	void Task();	

	std::thread::id getID() const;
	std::string getRelatedThreadName() const;

private:
	void Init();
	void WaitUntillStoped();

private:
	enum class State {
		NONE = 0,
		RUN,
		STOPED,
		DONE,
	};
	
	std::thread::id __threadID;
	std::shared_ptr<ThreadRunner> __runner;

	std::unique_ptr<ThreadRAII> __threadHolder;
	std::once_flag __startFlag;
	
	State __state;
	std::mutex __stateMutex;
	std::condition_variable __stateCondVariable;
};