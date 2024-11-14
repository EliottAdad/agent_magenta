/*
 * TimeLoop.h
 *
 *  Created on: 20 mai 2024
 *      Author: esn
 */

#ifndef TIMELOOP_H_
#define TIMELOOP_H_

#include <unordered_set>
#include "TimeSensitive.h"


class TimeLoop {
private:
	bool m_loop;
	std::unordered_set<TimeSensitive*> m_lst;			//List of time sensitive objects

public:
	TimeLoop();
	virtual ~TimeLoop();
	TimeLoop(const TimeLoop &other);

	void set(TimeSensitive* t);
	std::unordered_set<TimeSensitive*> get();
	void insert(TimeSensitive* t);
};


#endif /* TIMELOOP_H_ */

