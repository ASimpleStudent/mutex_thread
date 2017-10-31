//============================================================================
// Name        : 410_mutex.cpp
// for threads to work you must enable them in eclipse
// project name->Properties->C/C++ Build->Settings->GCC C++ Compiler-> Dialect
// ->Language Standard dropdown
// choose at least ISO C++11(-std=c++0x)
//add -pthread to the 'Other Dialect Flags' below above dropdown
//then in the GCC C++ Linker Libraries add the pthread library to the
//libraries-l text box on the right
//============================================================================
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
const int FIVE_MILLION = 5000000;

//global variable
int global2 = 0;

//traffic cop
mutex m;

//thread functions
void task_dec(int numbtimes) {
	//decrement

	for (int i = 0; i < numbtimes; i++) {
		m.lock();
		global2--;	//this one statement is the critical section
		m.unlock();
//		cout<<"in 1"<<endl;
	}
}

void task_inc(int numbtimes) {
	//increment

	for (int i = 0; i < numbtimes; i++) {
		m.lock();
		global2++;	//this one statement is the critical section
		m.unlock();
//		cout<<"in 2"<<endl;
	}
}

int main() {
	//how many cores do we have? BTW unsigned really? are we planning for 2**32 cores?
	unsigned num_cpus = std::thread::hardware_concurrency();

	// constructs 2 threads and runs
	thread t1(task_inc, FIVE_MILLION);
	thread t2(task_dec, FIVE_MILLION);

	// Makes the main thread wait for the new threads to finish execution, therefore blocks its own execution.
	t1.join();
	t2.join();

	std::cout << "Value of global      :" << global2 << " it should be 0"
			<< std::endl;
}

