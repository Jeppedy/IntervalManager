#ifndef _INTERVALMANAGER_H_
#define _INTERVALMANAGER_H_

#include <application.h>

class IntervalManager {
public:
    IntervalManager( uint32_t intervalIn ) ;

    boolean isTimeToRun( boolean autoMarkAsRun = true) ;
    void markAsRun() ;

private:
    uint32_t _interval ;
    uint32_t _lastRun ;
} ;

#endif

