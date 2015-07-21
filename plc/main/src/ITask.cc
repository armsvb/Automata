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
		


};//namespace Automata
