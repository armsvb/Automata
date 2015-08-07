#include "../../../main/include/Scheduler.h"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ITask
#include <boost/test/unit_test.hpp>



class OneShotMock1: public Automata::Scheduler::OneShot<bool>{

public:

	virtual void run(void){
		getPromise().set_value(true);
	}//virtual void run(void)

};//class OneShotMock1: public Automata::Scheduler::OneShot<bool>



BOOST_AUTO_TEST_CASE( OneShot__baseTest ){

	Automata::Scheduler::OneShot<bool>*task = new OneShotMock1();
	
	std::future<bool> future = task->getFuture();
	
	task->run();
	future.wait();
	
	BOOST_CHECK( future.get() );

}

BOOST_AUTO_TEST_CASE( OneShot__Lambda ){

	Automata::Scheduler::OneShot<bool>*task = new Automata::Scheduler::OneShot<bool> ( []() { return true;} );
	
	std::future<bool> future = task->getFuture();
	
	task->run();
	future.wait();
	
	BOOST_CHECK( future.get() );

}


BOOST_AUTO_TEST_CASE( OneShot__Lambda_False ){

	Automata::Scheduler::OneShot<bool>*task = new Automata::Scheduler::OneShot<bool> ( []() { return false;} );
	
	std::future<bool> future = task->getFuture();
	
	task->run();
	future.wait();
	
	BOOST_CHECK( !future.get() );

}


BOOST_AUTO_TEST_CASE( OneShot__Lambda_Double ){

	double t1 = 7.0;
	double t2 = 42.0;

	Automata::Scheduler::OneShot<double>*task = new Automata::Scheduler::OneShot<double> ( [&]() { return t1-t2;} );
	
	std::future<double> future = task->getFuture();
	
	task->run();
	future.wait();
	
	BOOST_CHECK( future.get() < 0.0 );

}
