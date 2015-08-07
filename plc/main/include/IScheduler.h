/*
This file is part of Automata PLC.

    Automata PLC is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Automata PLC is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Automata PLC.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <atomic>
#include <memory>
#include <future>

namespace Automata{
	namespace Scheduler{

		template<class T>
		class ITask;
		class IScheduler;

		/** Execution queue for scheduled task.
		 *
		 */
		enum QUEUE{

			QUEUE_PROGRAM = 0, 	///< PLC Program that should execute consecutively in the main thread
			QUEUE_IO = 1		///< IO tasks that should execute asynchronously in a separate thread

		};//enum QUEUE
	
		/** Task execution type
		*
		*/
		enum TASK_TYPE{
	
			TASK_ONE_SHOT = 0, 	///< Executes task once
			TASK_INTERVAL = 1 	///< Reoccuring task
	
		};//enum TASK_TYPE

	
		template<class T>
		class ITask{
		public:
	
			ITask(){}
			virtual ~ITask(){}

			/** called to run the task
			*
			*/
			virtual void run(void)=0;
					
			/** returns the type of task
			*
			*/
			virtual TASK_TYPE getTaskType(void)=0;
		
			/** return the task's future.
			*
			* the value will be true if the task completed. If the task failed or was canceled it will be false.
			*/
			virtual std::future<T> getFuture(void)=0;
		
			/** returns a positive number in seconds for the next time to execute.
			* If the value if <= 0 or NaN the task will not be rescheduled
			*/
			virtual double nextInterval(void)=0;

		};//class ITask
	
	
		template<class T>
		class OneShot: public ITask<T>{
		private:
		
			std::atomic_bool isExecuting;
			std::promise<T> promise;
			std::function<T (void)> task;
			
		protected:
		
			/** returns the task's promise
			*/
			virtual std::promise<T>& getPromise(void){
				return promise;	
			}
		
		public:
	
			/** Default constructor.
			*
			*/
			OneShot(){
				isExecuting=false;
				task = nullptr;
			}
			
			/** Lambda constructor.
			*
			*/
			OneShot(std::function<T (void)> task){
				isExecuting=false;
				this->task = task;
			}
		
			/** destructor.
			*/
			~OneShot(){
			
			}
		
			/** called to run the task
			*
			*/
			virtual void run(void){
				getPromise().set_value(task());
			}
		
			/** returns the type of task
			*
			*/
			virtual TASK_TYPE getTaskType(void){
				return TASK_TYPE::TASK_ONE_SHOT;
			}
		
			/** return the task's future.
			*
			* the value will be true if the task completed. If the task failed or was canceled it will be false.
			*/
			virtual std::future<T> getFuture(void){
				return promise.get_future();
			}
		
			/** returns a positive number in seconds for the next time to execute.
			* If the value if <= 0 or NaN the task will not be rescheduled
			*/
			virtual double nextInterval(void){
				return -1;
			}
		
		
		};//class OneShot: public ITask
		


		/** Task scheduler interface.
		*
		* Performs tasks related to task scheduling
		*
		*/
		class Scheduler{
		private:
			Scheduler(){};
		
		public:
		
			~Scheduler(){};
		
			std::shared_ptr<Scheduler> getInstance(void);
		
			/** Schedules a task to be completed at some point in the future.
			*
			*	The task will executed approximately "time" seconds in the future, then
			* 	removed from the queue. If task type is TASK_PROGRAM the task will be executed
			*	on the main thread. If the task type is TASK_IO the task will be executed
			*	asynchronously in a separate thread.
			*/
			//std::shared_ptr<TaskPromise> once(std::shared_ptr<TaskPromise> task,QUEUE type,float time);
		
	
		};//class Scheduler
	}//namespace Scheduler
}//namespace Automata
