/* Written by Avinash Dongre <dongre.avinash@gmail.com> 
 * and placed in the public domain.
 */
#include <iostream>
#include "Timer.h"

Timer::Timer () {
	label = "Process Timer";
	reset();
}

Timer::Timer (const std::string &label) {
	Timer::label = label;
	reset();
	start();
}

Timer::~Timer() {
}

void Timer::reset()
{
	tps = sysconf ( _SC_CLK_TCK );
	end_time = 0;
	usertime = 0;
	systemtime = 0;
	elapsedtime = 0;
	waittime = 0;
}

void Timer::start() {
	start_time = times(&(start_cpu_time));
}

void Timer::show() {
	std::cout 
		<< "  "
		<< label << "\n"
		<< "  -------------------------------\n"
		<< "  User CPU Time  : "
		<< usertime << " s\n"
		<< "  System CPU Time: "
		<< systemtime << " s\n"
		<< "  Wait Time      : "
		<< waittime << " s\n"
		<< "  -------------------------------\n"
		<< "  Elapsed Time   : "
		<< elapsedtime << " s\n" << std::endl;
}

void Timer::stop() {
	end_time = times(&end_cpu_time);
	elapsedtime = ((double)(end_time - start_time )/(double)tps );
	if (elapsedtime < 0.001) {
		elapsedtime = 0.001;
	}

	usertime = ((double)(end_cpu_time.tms_utime - start_cpu_time.tms_utime)/(double)tps);
	systemtime = ((double)(end_cpu_time.tms_stime - start_cpu_time.tms_stime)/(double)tps);
	waittime = (elapsedtime - (usertime + systemtime));
	if ( waittime < 0.00 ) {
		waittime = 0.00;
	}
	show();
}

double Timer::get_user_time(void) {
	return usertime;
}

double Timer::get_system_time(void) {
	return systemtime;
}

double Timer::get_wait_time(void) {
	return waittime;
}

double Timer::get_non_wait_time(void) {
	return usertime + systemtime;
}

double Timer::get_elapsed_time(void) {
	return elapsedtime;
}

