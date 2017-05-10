#include "commonThread.h"


tThread::tThread(){
}

void tThread::start(){
	thread = std::thread(&tThread::run, this);
}

void tThread::join(){
	thread.join();
}

tThread::tThread(tThread&& other){
	this->thread = std::move(other.thread);
}

tThread& tThread::operator=(tThread&& other){
		this->thread = std::move(other.thread);
		return *this;
}
