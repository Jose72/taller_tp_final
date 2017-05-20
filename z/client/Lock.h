//
// Created by matias on 20/05/17.
//

#ifndef CLIENT_LOCK_H
#define CLIENT_LOCK_H

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

#endif //CLIENT_LOCK_H
