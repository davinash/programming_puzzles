/* Written by Avinash Dongre <dongre.avinash@gmail.com> 
 * and placed in the public domain.
 */
#ifndef TIMER_H
#define TIMER_H

#include <ctime>
#include <string>

#include <sys/times.h>
#include <unistd.h>

class Timer {
	public:
		Timer();
		Timer(const std::string &label);
		~Timer();
		void start();
		void stop();
		void show();
		double get_user_time();
		double get_system_time();
		double get_wait_time();
		double get_elapsed_time();
		double get_non_wait_time();
	private:
		void reset();
		std::string label;
		long tps;
		long start_time, end_time;
		double usertime, systemtime, elapsedtime, waittime;
		struct tms start_cpu_time, end_cpu_time;
};
#endif
