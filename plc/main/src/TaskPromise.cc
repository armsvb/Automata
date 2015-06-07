#include "IScheduler.h"

namespace Automata{

	

	TaskPromise::TaskPromise(){
	
		_complete=false;
		_success=false;
		_canceled=false;
		
	}//TaskPromise::TaskPromise()

	TaskPromise::~TaskPromise(){

	}//virtual TaskPromise::~TaskPromise()
	
	void TaskPromise::setFailed(void){
		_success=false;
		_complete=true;
		_canceled=false;
	}//void TaskPromise::setFailed(void)

	void TaskPromise::setSuccess(void){
		_success=true;
		_complete=true;
		_canceled=false;
	}//void TaskPromise::setSuccess(void)
	
	void TaskPromise::setCanceled(void){
		_success=false;
		_complete=false;
		_canceled=true;
	}//void TaskPromise::setCanceled(void)

	bool TaskPromise::isComplete(void){
		return _complete;
	}//bool TaskPromise::isComplete(void)

	bool TaskPromise::isSuccess(void){
		return _success;
	}//bool TaskPromise::isSuccess(void)
	
	bool TaskPromise::isCanceled(void){
		return _canceled;
	}//bool TaskPromise::isCanceled(void)
	
	void TaskPromise::onSuccess(std::shared_ptr<ITask> task){
	
	}//void TaskPromise::onSuccess(ITask*task)
	
	void TaskPromise::onFailure(std::shared_ptr<ITask> task){
	
	}//void TaskPromise::onFailure(ITask*task)
	
	void TaskPromise::onCancel(std::shared_ptr<ITask> task){
	
	}//void TaskPromise::onCancel(ITask*task)
	

}//namespace Automata
