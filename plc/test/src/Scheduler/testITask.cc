#include "../../../main/include/IScheduler.h"

//#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ITask
#include <boost/test/unit_test.hpp>


class ITaskMock1: public Automata::ITask{

public:

	virtual void run(void){
	
	}//virtual void run(void)

};//class ITaskMock1: public Automata::ITask

BOOST_AUTO_TEST_CASE( getPromise ){

	Automata::ITask*task = new ITaskMock1();
	
	std::shared_ptr<Automata::TaskPromise> promise;
	
	promise = task->getPromise();
	
	BOOST_CHECK( promise );

}
