//this is thread.cc
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex restriction;
void thread(string test) {
  unique_lock<mutex> locked(restriction);
  cout << Persona << ", this is the first test" << endl;
  this_thread::sleep_for(chrono::seconds(2));
  cout << Persona << ", this is the second test" << endl;
  locked.unlock();
}

