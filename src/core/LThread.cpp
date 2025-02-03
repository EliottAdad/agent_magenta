/*
 * LThread.cpp
 *
 *  Created on: 3 févr. 2025
 *      Author: esn
 */

#include "LThread.h"

LThread::LThread() {
	// TODO Auto-generated constructor stub

}

LThread::~LThread() {
	abortAndJoin();
}

LThread::LThread(const LThread& lthread) {
	// TODO Auto-generated constructor stub

}

// To be called, once the looper should start looping.
bool LThread::run() {
	try{
		mThread = std::thread(&LThread::runFunc, this);
	}
	catch(...){
		return false;
	}

	return true;
}



bool LThread::running() const {
	return mRunning.load();
}

void LThread::stop() {
	abortAndJoin();
}

// Conditionally-infinite loop doing sth. iteratively
void LThread::runFunc() {
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
void LThread::abortAndJoin() {
    mAbortRequested.store(true);
    if(mThread.joinable())
    {
        mThread.join();
    }
}




