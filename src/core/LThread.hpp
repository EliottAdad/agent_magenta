/*
 * LThread.hpp
 *
 *  Created on: 3 févr. 2025
 *      Author: esn
 */

#ifndef LTHREAD_HPP_
#define LTHREAD_HPP_


#include <thread>
#include <atomic>
#include <memory>
#include <functional>
#include <stdexcept>

/**
 * LThread
 * Looping thread.
 */
class LThread {
private:
    std::thread mThread;
    std::atomic_bool mRunning;
    std::atomic_bool mAbortRequested;

    // Conditionally-infinite loop doing sth. iteratively
    void runFunc();

    // Shared implementation of exiting the loop-function and joining to the main thread.
    void abortAndJoin();

public:
    LThread();
	virtual ~LThread();
	LThread(const LThread& lthread);

	// To be called, once the looper should start looping.
	bool run();

	bool running() const;
	void stop();

};


#endif /* LTHREAD_HPP_ */
