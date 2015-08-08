#include <iostream>
#include <queue>
#include <vector>

#include "Scheduler.h"

namespace Automata{
	namespace Scheduler{
		
		
		struct QueueTask{
			std::shared_ptr<ITask> task;
			std::chrono::steady_clock::time_point next;
		};		
		bool operator<(QueueTask a,QueueTask b) { return a.next > b.next; };	
		
		struct Scheduler::Impl{
		
			Scheduler* scheduler;
		
			std::thread thread[2];
			
			std::atomic_bool exit;
			
		
		
			void initThread(QUEUE index);
			
			std::mutex queueLock[2];
			std::priority_queue<QueueTask> queue[2];
			std::atomic<uint64_t> cycleCounts[2];
			
		};
		
		
		
		
		Scheduler::Scheduler(){
			_impl = std::unique_ptr<Impl>(new Impl());
			_impl->scheduler = this;
			_impl->exit = false;
			_impl->cycleCounts[0] =_impl->cycleCounts[1] = 0;
			_impl->queue[0] = std::priority_queue<QueueTask>();
			_impl->queue[0] = std::priority_queue<QueueTask>();
			
			run();
		}
			
		void Scheduler::run(void){
		
			_impl->initThread(QUEUE::QUEUE_IO);
			_impl->initThread(QUEUE::QUEUE_PROGRAM);
			
		}
		
		void Scheduler::Impl::initThread(QUEUE index){
			thread[index] = std::thread( [=](){
					
					while(!exit){
						cycleCounts[index]++;
						
						QueueTask qt;
						bool run=false;
						{
							std::lock_guard<std::mutex> lock(queueLock[index]);
							if(!queue[index].empty()){
								qt = queue[index].top();
								
								if(qt.next <= std::chrono::steady_clock::now()){
									run=true;
									queue[index].pop();
								}
							}
						}
						
						if(run){
							qt.task->run();
							
							double interval = qt.task->nextInterval();
							if(interval > 0.0){
								scheduler->schedule(index,interval,qt.task);
							}
						}
					}
	
				});
		}
		
		
		std::shared_ptr<ITask> Scheduler::schedule(QUEUE type,double time, std::shared_ptr<ITask> task){
		
			std::chrono::milliseconds dur((long int)(time*1000.0));
				
			QueueTask qt;
			qt.task = task;
			qt.next = std::chrono::steady_clock::now() + dur;
		
			{
				std::lock_guard<std::mutex> lock(_impl->queueLock[type]);
				_impl->queue[type].push(qt);
			}
			
			return task;
		}
		
		void Scheduler::exit(void){
			_impl->exit = true;
		}
		
		uint64_t Scheduler::getIOCycleCount(void){
			return _impl->cycleCounts[QUEUE::QUEUE_IO];
		}
		
		uint64_t Scheduler::getProgramCycleCount(void){
			return _impl->cycleCounts[QUEUE::QUEUE_PROGRAM];
		}
		
		
		Scheduler::~Scheduler(){
			_impl->thread[0].join();
			_impl->thread[1].join();
		
		}

	}//namespace Scheduler
}//namespace Automata
