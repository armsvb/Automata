#include "../../../main/include/IScheduler.h"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TaskPromise
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( isSuccess ){
	Automata::TaskPromise promise;

	BOOST_CHECK( !promise.isComplete() );
	BOOST_CHECK( !promise.isSuccess() );
	
	promise.setSuccess();
	
	BOOST_CHECK( promise.isComplete() );
	BOOST_CHECK( promise.isSuccess() );
}

BOOST_AUTO_TEST_CASE( isSuccess_Failure ){
	Automata::TaskPromise promise;
	
	BOOST_CHECK( !promise.isComplete() );
	BOOST_CHECK( !promise.isSuccess() );
	
	promise.setFailed();
	
	BOOST_CHECK( promise.isComplete() );
	BOOST_CHECK( !promise.isSuccess() );

}


BOOST_AUTO_TEST_CASE( isCanceled ){
	Automata::TaskPromise promise;
	
	promise.setSuccess();
	promise.setCanceled();
	
	BOOST_CHECK( promise.isCanceled() );
	BOOST_CHECK( !promise.isComplete() );
	BOOST_CHECK( !promise.isSuccess() );

}

class TestTaskPromiseTask: public Automata::ITask{
public:

	

}

BOOST_AUTO_TEST_CASE( onSuccess ){
	Automata::TaskPromise promise;
	
	

}

BOOST_AUTO_TEST_CASE( isSuccess_WithValue ){
	Automata::TaskPromiseWithValue<int> promise;
	
	BOOST_CHECK( !promise.isComplete() );
	BOOST_CHECK( !promise.isSuccess() );
	
	std::shared_ptr<int> result(new int(42));
	promise.setFailed(result);
	
	BOOST_CHECK( promise.isComplete() );
	BOOST_CHECK( !promise.isSuccess() );
	BOOST_CHECK_EQUAL( *promise.getValue(), 42);

}
