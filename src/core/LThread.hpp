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








inline LThread::LThread() {
	// TODO Auto-generated constructor stub

}

inline LThread::~LThread() {
	abortAndJoin();
}

inline LThread::LThread(const LThread& lthread) {
	// TODO Auto-generated constructor stub

}

// To be called, once the looper should start looping.
inline bool LThread::run() {
	try{
		mThread = std::thread(&LThread::runFunc, this);
	}
	catch(...){
		return false;
	}

	return true;
}



inline bool LThread::running() const {
	return mRunning.load();
}

inline void LThread::stop() {
	abortAndJoin();
}

// Conditionally-infinite loop doing sth. iteratively
inline void LThread::runFunc() {
    mRunning.store(true);

    // We now check against abort criteria
    while(false == mAbortRequested.load())
    {
        try
        {
            // Do something...
        }
        catch(std::runtime_error& e)
        {
            // Some more specific
        }
        catch(...)
        {
            // Make sure that nothing leaves the thread for now...
        }
    }

    mRunning.store(false);

}

// Shared implementation of exiting the loop-function and joining
// to the main thread.
inline void LThread::abortAndJoin() {
    mAbortRequested.store(true);
    if(mThread.joinable())
    {
        mThread.join();
    }
}



#endif /* LTHREAD_HPP_ */
