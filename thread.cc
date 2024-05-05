//this is thread.cc
#include <iostream>
#include <thread>
using namespace std;

void thread(string test) {
  cout << Persona << ", this is the first test" << endl;
  this_thread::sleep_for(chrono::seconds(2));
  cout << Persona << ", this is the second test" << endl;

}
