
#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <string>
#include <iostream>

inline std::chrono::high_resolution_clock::time_point getTime()
{
	return std::chrono::high_resolution_clock::now();
}

inline void printTimeDifferenceMillis(const std::chrono::high_resolution_clock::time_point &t1, const std::chrono::high_resolution_clock::time_point &t2)
{
	std::cout << "Delta: " << std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()) << " ms" << std::endl;
}

inline void printTimeDifferenceAll(const std::chrono::high_resolution_clock::time_point &t1, const std::chrono::high_resolution_clock::time_point &t2)
{
	std::cout << "Delta: "
		<< std::to_string(std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count()) << "s "
		<< std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()) << "ms "
		<< std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()) << "ns"
		<< std::endl;
}

#endif