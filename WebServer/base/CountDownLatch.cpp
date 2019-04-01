
#include "CountDownLatch.h"

CountDownLatch::CountDownLatch(int count)
:   mutex_(),
    condition_(mutex_),
    count_(count)
{}
    
void CountDownLatch::wait()
{
    MutexLockGuard lock(mutex_);
    --count_;
    if(count == 0)
	condition_.notifyAll();
}
