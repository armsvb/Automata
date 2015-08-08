#include "../../../main/include/Scheduler.h"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Scheduler
#include <boost/test/unit_test.hpp>

#include <chrono>
#include <thread>
#include <iostream>

BOOST_AUTO_TEST_CASE( Scheduler__once ){

	std::shared_ptr<Automata::Scheduler::Scheduler> scheduler = std::make_shared<Automata::Scheduler::Scheduler>();
	
	int counter = 0;
	
	std::shared_ptr<Automata::Scheduler::OneShot<bool>> task = std::shared_ptr<Automata::Scheduler::OneShot<bool>>(new Automata::Scheduler::OneShot<bool>( [&]() { counter++; return true; } ));
	scheduler->once(Automata::Scheduler::QUEUE::QUEUE_IO,0.1, task );
	
	task->getFuture().wait();
	
	scheduler->exit();
	
	BOOST_CHECK(counter == 1);
}


BOOST_AUTO_TEST_CASE( Scheduler__once_lambda ){

	std::shared_ptr<Automata::Scheduler::Scheduler> scheduler = std::make_shared<Automata::Scheduler::Scheduler>();
	
	int counter = 0;
	
	auto task = scheduler->once<void>(Automata::Scheduler::QUEUE::QUEUE_IO,0.1, [&]() { counter++; } );
	
	task->getFuture().wait();
	
	scheduler->exit();
	
	BOOST_CHECK(counter == 1);
}

BOOST_AUTO_TEST_CASE( Scheduler__onceIO_lambda ){

	std::shared_ptr<Automata::Scheduler::Scheduler> scheduler = std::make_shared<Automata::Scheduler::Scheduler>();
	
	int counter = 0;
	
	auto task = scheduler->onceIO<void>( [&]() { counter=42; } );
	
	task->getFuture().wait();
	
	scheduler->exit();
	
	BOOST_CHECK(counter == 42);
}


BOOST_AUTO_TEST_CASE( Scheduler__onceProgram_lambda ){

	std::shared_ptr<Automata::Scheduler::Scheduler> scheduler = std::make_shared<Automata::Scheduler::Scheduler>();
	
	int counter = 0;
	
	auto task = scheduler->onceProgram<void>( 0.01,  [&]() { counter=7; } );
	
	task->getFuture().wait();
	
	scheduler->exit();
	
	BOOST_CHECK(counter == 7);
}

BOOST_AUTO_TEST_CASE( Scheduler__once_order ){

	std::shared_ptr<Automata::Scheduler::Scheduler> scheduler = std::make_shared<Automata::Scheduler::Scheduler>();
	
	int num = 42;
	
	std::shared_ptr<Automata::Scheduler::OneShot<bool>> task = std::shared_ptr<Automata::Scheduler::OneShot<bool>>(new Automata::Scheduler::OneShot<bool>( [&]() { num+=4; return true; } ));
	scheduler->once(Automata::Scheduler::QUEUE::QUEUE_IO,0.01, task );
	
	std::shared_ptr<Automata::Scheduler::OneShot<bool>> task2 = std::shared_ptr<Automata::Scheduler::OneShot<bool>>(new Automata::Scheduler::OneShot<bool>( [&]() { num/=5; return true; } ));
	scheduler->once(Automata::Scheduler::QUEUE::QUEUE_IO,0.03, task2 );
	
	std::shared_ptr<Automata::Scheduler::OneShot<bool>> task3 = std::shared_ptr<Automata::Scheduler::OneShot<bool>>(new Automata::Scheduler::OneShot<bool>( [&]() { num*=9; return true; } ));
	scheduler->once(Automata::Scheduler::QUEUE::QUEUE_IO,0.02, task3 );
		
	task->getFuture().wait();
	task2->getFuture().wait();
	task3->getFuture().wait();
	
	scheduler->exit();
	
	BOOST_CHECK(num == 82); // if the priority queue is working properly, num will equal 82
}


BOOST_AUTO_TEST_CASE( Scheduler__once_delay ){

	std::shared_ptr<Automata::Scheduler::Scheduler> scheduler = std::make_shared<Automata::Scheduler::Scheduler>();
	
	int counter = 0;
	
	std::shared_ptr<Automata::Scheduler::OneShot<bool>> task = std::shared_ptr<Automata::Scheduler::OneShot<bool>>(new Automata::Scheduler::OneShot<bool>( [&]() { counter++; return true; } ));
	scheduler->once(Automata::Scheduler::QUEUE::QUEUE_IO,0.3, task );
	
	auto start = std::chrono::high_resolution_clock::now();
	
	task->getFuture().wait();
	
	auto end = std::chrono::high_resolution_clock::now();
	
	
	
	scheduler->exit();
	
	BOOST_CHECK( (end-start) >= std::chrono::milliseconds(300) );
	BOOST_CHECK(counter == 1);
}



BOOST_AUTO_TEST_CASE( Scheduler__interval ){

	std::shared_ptr<Automata::Scheduler::Scheduler> scheduler = std::make_shared<Automata::Scheduler::Scheduler>();
	
	int counter = 0;
	
	std::shared_ptr<Automata::Scheduler::Interval> task = std::shared_ptr<Automata::Scheduler::Interval>(new Automata::Scheduler::Interval( 0.001, [&]() { counter++; } ));
	scheduler->interval(Automata::Scheduler::QUEUE::QUEUE_IO, task );
	
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	
	
	scheduler->exit();
	
	BOOST_CHECK(counter >= 9);
}


BOOST_AUTO_TEST_CASE( Scheduler__interval_lambda ){

	std::shared_ptr<Automata::Scheduler::Scheduler> scheduler = std::make_shared<Automata::Scheduler::Scheduler>();
	
	int counter = 0;
	
	auto task = scheduler->interval(Automata::Scheduler::QUEUE::QUEUE_IO, 0.001, [&]() { counter++; } );
	
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	
	scheduler->exit();
	
	BOOST_CHECK(counter >= 9);
}


BOOST_AUTO_TEST_CASE( Scheduler__interval_cancel ){

	std::shared_ptr<Automata::Scheduler::Scheduler> scheduler = std::make_shared<Automata::Scheduler::Scheduler>();
	
	int counter = 0;
	
	auto task = scheduler->interval(Automata::Scheduler::QUEUE::QUEUE_IO, 0.001, [&]() { counter++; } );
	
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	
	task->cancel();
	
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	
	scheduler->exit();
	
	BOOST_CHECK(counter >= 9 && counter <= 11);
}

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
