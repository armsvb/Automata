#include "../../../main/include/IScheduler.h"

//#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ITask
#include <boost/test/unit_test.hpp>



class ITaskMock1: public Automata::ITask{

public:

	virtual void run(void){
	
	}//virtual void run(void)

};//class ITaskMock1: public Automata::ITask


template<typename T>
class ITaskMock2: public Automata::TaskBase<T>{

public:

	virtual void run(void){
		std::dynamic_pointer_cast<Automata::TaskPromiseWithValue<int>>(this->getPromise())->setSuccess(42);
		
	}//virtual void run(void)

};//class ITaskMock1: public Automata::ITask

BOOST_AUTO_TEST_CASE( ITask__getPromise ){

	Automata::ITask*task = new ITaskMock1();
	
	std::shared_ptr<Automata::TaskPromise> promise;
	
	promise = task->getPromise();
	
	BOOST_CHECK( promise );

}

BOOST_AUTO_TEST_CASE( TaskBase ){

	Automata::TaskBase<int>*task = new ITaskMock2<int>();
	
	std::shared_ptr<Automata::TaskPromiseWithValue<float>> promise;
	
	
	promise = std::dynamic_pointer_cast<Automata::TaskPromiseWithValue<float>>(task->getPromise());
	
	BOOST_CHECK( promise );
	
	
	BOOST_CHECK(promise->getValue() == 42);


}
