#ifndef TTHREAD_H
#define TTHREAD_H


#include <thread>



class tThread {
    private:
        std::thread thread;
 
    public:
        tThread();
        void start(); 
        void join();
        virtual void run() = 0; 
        virtual void stop() = 0; 
	tThread(const tThread&) = delete;
        tThread& operator=(const tThread&) = delete;
        virtual ~tThread() {} 
	tThread(tThread&& other);
        tThread& operator=(tThread&& other);
};

#endif

