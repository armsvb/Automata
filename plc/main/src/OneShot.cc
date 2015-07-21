#include "IScheduler.h"

namespace Automata{
	namespace Scheduler{
		
		struct OneShot::Impl{
			std::atomic_bool isExecuting;
			std::promise<bool> promise;	
			
			Impl(){
				isExecuting=false;
			}
			
		};
		
		OneShot::OneShot(){
			_impl = std::unique_ptr<Impl>(new Impl());
		}

		OneShot::~OneShot(){
		
		}
		
		std::promise<bool>& OneShot::getPromise(void){
			return _impl->promise;
		}

		TASK_TYPE OneShot::getTaskType(void){
			return TASK_TYPE::TASK_ONE_SHOT;
		}

		std::future<bool> OneShot::getFuture(void){
			return _impl->promise.get_future();
		}

		double OneShot::nextInterval(void){
			return -1;
		}

	}//namespace Scheduler
}//namespace Automata
