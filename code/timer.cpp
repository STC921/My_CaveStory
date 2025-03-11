#include "timer.h"

std::set<Timer*> Timer::timers_;

void Timer::updateAll(units::MS elapsed_time){
	for (std::set<Timer*>::iterator iter = timers_.begin();
		iter != timers_.end();
		++iter){
		(*iter)->update(elapsed_time);
	}
}