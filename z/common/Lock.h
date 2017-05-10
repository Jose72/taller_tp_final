#ifndef TLOCK_H
#define TLOCK_H

#include <mutex>

class tLock {
	private:
		std::mutex &m;
		
	public:
		explicit tLock(std::mutex &m);
		~tLock();
		tLock(const tLock&) = delete;
		tLock& operator=(const tLock&) = delete;
		tLock(tLock&&) = delete;
		tLock& operator=(tLock&&) = delete;
};

#endif
