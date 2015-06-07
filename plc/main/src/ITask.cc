#include "IScheduler.h"

namespace Automata{


		ITask::ITask(){
			_promise = std::shared_ptr<TaskPromise>(new TaskPromise());
		}
		
		ITask::~ITask(){
		
		}
		
		std::shared_ptr<TaskPromise> ITask::getPromise(){
			return _promise;
		}
		
		void ITask::cancel(void){
		
		}
		
		
		template<typename T>
		TaskBase<T>::TaskBase():
			ITask(){
			_promise = std::shared_ptr<TaskPromise>(new TaskPromiseWithValue<T>());
		}


};//namespace Automata
