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

namespace Automata{

	/** Execution type for scheduled task.
	 *
	 */
	enum TASK_TYPE{

		TASK_PROGRAM = 0, ///< PLC Program that should execute consecutively in the main thread
		TASK_IO = 1			///< IO tasks that should execute asynchronously in a separate thread

	};//enum TASK_TYPE

	/** Current state of the task.
	 *
	 */
	enum TASK_STATE{

		STATE_WAITING = 0,	///< Task is waiting in the queue
		STATE_RUNNING = 1,	///< Task is currently executing
		STATE_COMPLETE = 2, ///< Task is complete
		STATE_EXCEPTION = 3 ///< There was an exception while executing the task

	};// enum TASK_STATE

	/** Base class for task promises.
	 *
	 * Provided basic complete, not complete status, as well as success, failure status
	 * If more return data is needed this class can be inherited from.
	 *
	 */
	class TaskPromise{
	private:
	
		std::atomic_bool _complete;
		std::atomic_bool _success;

	protected:

		

	public:
		TaskPromise();
		virtual ~TaskPromise();

		/** Returns true if the task has completed.
		 *
		 * Does not indicate if the task complete successfully or failed. Only indicates that the
		 * task was started, and has now finished executing.
		 *
		 * @see isSuccess()
		 */
		bool isComplete(void);

		/** Returns true if the task completed successfully.
		 *
		 * Only true if the task has completed successfully. Check isComplete before checking isSuccess
		 * to determine if the task has completed.
		 *
		 * @see isComplete()
		 */
		bool isSuccess(void);
		
		/** Sets the promise result to complete with failure.
		 *
		 * isComplete will return true and isSuccess will return false
		 *
		 */
		void setFailed(void);

		/** Sets the promise result to complete with success.
		 *
		 * isComplete will return true and isSuccess will return true
		 *
		 */
		void setSuccess(void);


	};// class TaskPromiseBase

	class ITask{
	public:
		ITask(){};
		virtual ~ITask(){};

		virtual void run(std::shared_ptr<TaskPromise> promise)=0;

	};

	/** Task scheduler interface.
	*
	* Performs tasks related to task scheduling
	*
	*/
	class IScheduler{
	public:
		IScheduler(){};
		virtual ~IScheduler(){};
		
		/** Schedules a task to be completed at some point in the future.
		*
		*	The task will executed approximately "time" seconds in the future, then
		* 	removed from the queue. If task type is TASK_PROGRAM the task will be executed
		*	on the main thread. If the task type is TASK_IO the task will be executed
		*	asynchronously in a separate thread.
		*/
		virtual std::shared_ptr<TaskPromise> once(std::shared_ptr<TaskPromise> task,TASK_TYPE type,float time) = 0;
		
	
	};//class IScheduler

}//namespace Automata
