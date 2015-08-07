#include "../../../main/include/IScheduler.h"

//#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ITask
#include <boost/test/unit_test.hpp>



class IntervalMock1: public Automata::Scheduler::Interval{

public:

	IntervalMock1():
		Automata::Scheduler::Interval(1.0){
		
	}

	int runCount = 0;

	virtual void run(void){
		runCount++;
	}//virtual void run(void)

};//class IntervalMock1: public Automata::Scheduler::Interval



BOOST_AUTO_TEST_CASE( Interval__baseTest ){

	IntervalMock1*task = new IntervalMock1();
	
		
	task->run();
	task->run();
	task->run();
	
	
	BOOST_CHECK( task->runCount == 3 );

}

BOOST_AUTO_TEST_CASE( Interval__Lambda ){

	int count = 0;
	
	Automata::Scheduler::Interval*task = new Automata::Scheduler::Interval(1.5, [&]() { count++; } );
	
		
	task->run();
	task->run();
	task->run();
	task->run();
	
	
	BOOST_CHECK( count == 4 );

}
