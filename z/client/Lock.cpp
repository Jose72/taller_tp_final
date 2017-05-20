
#include "Lock.h"

tLock::tLock(std::mutex &m) : m(m) {
    m.lock();
}

tLock::~tLock() {
    m.unlock();
}
