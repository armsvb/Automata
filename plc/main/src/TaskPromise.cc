#include "IScheduler.h"

namespace Automata{

	

	TaskPromise::TaskPromise(){
	
		_complete=false;
		_success=false;
		
	}//TaskPromise::TaskPromise()

	TaskPromise::~TaskPromise(){

	}//virtual TaskPromise::~TaskPromise()
	
	void TaskPromise::setFailed(void){
		_success=false;
		_complete=true;
	}//void TaskPromise::setFailed(void)

	void TaskPromise::setSuccess(void){
		_success=true;
		_complete=true;
	}//void TaskPromise::setSuccess(void)

	bool TaskPromise::isComplete(void){
		return _complete;
	}//bool TaskPromise::isComplete(void)

	bool TaskPromise::isSuccess(void){
		return _success;
	}//bool TaskPromise::isSuccess(void)

}//namespace Automata
