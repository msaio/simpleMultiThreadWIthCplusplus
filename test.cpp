#include <iostream>
#include <thread>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <typeinfo>
#include <vector>
#include <mutex>
#include <cstdlib>

#include <unistd.h>


using namespace std;
using std::chrono::system_clock;

// simple function
void func(string name, int id){
	cout << name << " : " << id;
	cout << endl;
}
// class for testing
class obj{
	private:
		string name;
		int id;
	public:
		//constructor
		obj(){
			this->name = "|empty|";
			this->id = 0;
		}
		obj(string x){
			this->name = x;
			this->id = 0;
		}
		obj(string x, int i){
			this->name = x;
			this->id = i;
		}
		// methods
		void method_without_parameter(){
			cout << this->name << " : " << this->id << endl;
		}
		void method_with_parameter(string str){
			cout << std::this_thread::get_id() << endl;

			//sleep while next minute is not reached

			//get current time
			time_t timet = system_clock::to_time_t(system_clock::now());
			//convert it to tm struct
			struct tm * time = localtime(&timet);
			cout << "Current time: " << put_time(time, "%X") << '\n';
			// std::cout << "Waiting for the next minute to begin...\n";
			// time->tm_min++; time->tm_sec = 0;
			// //sleep until next minute is not reached
			// this_thread::sleep_until(system_clock::from_time_t(mktime(time)));
			// cout << std::put_time(time, "%X") << " reached!\n";

			// the compile code here
			cout << this->name << " : " << this->id << endl;
			//

			//sleep for 5 seconds
			cout << "Sleep for 3s..." << endl;
			this_thread::sleep_for(chrono::seconds(3));
		
			// the compile code here
			cout << " likes " << str << endl;
			//

			//get current time
			timet = system_clock::to_time_t(system_clock::now());
			//convert it to tm struct
			time = std::localtime(&timet);
			cout << "Current time: " << put_time(time, "%X") << '\n';
		}
		// getter and setter
		string get_name(){return this->name;}
		int get_id(){return this->id;};
		void set_name(string name){this->name = name;}
		void set_id(int id){this->id = id;}
};
// Mutex for concurrent access to resources
std::mutex m;
vector<int> vec;
// Simple push and pop
void push(){
	m.lock();
		for (int i = 0; i != 10; ++i){
			cout << "Push " << i << endl;
			sleep(1);
			vec.push_back(i);
		}
	m.unlock();
}
void pop(){
	m.lock();
	for (int i = 0; i != 10; ++i){
		if (vec.size() > 0){
			int val = vec.back();
			vec.pop_back();
			cout << "Pop " << val << endl;
		}
	sleep(1);
	}
	m.unlock();
}
// Make A Call
void make_a_call(){
	m.lock();//person enters the call box and locks the door
	//now it can talk to his friend without any interruption
	cout << " Hello my friend, this is " << this_thread::get_id() << endl;
	//this person finished to talk to his friend
	m.unlock();//and he leaves the call box and unlock the door
}
// Main
int main(){
	//create thread with object and passing argument with sleeping time
	obj o = obj("mr.D", 1031);
	thread t(&obj::method_with_parameter, o, "jav");
	if(t.joinable()) t.join();
	else cout << "Error!\n";

	//create two threads
	thread pu(push);
	thread po(pop);
	if (pu.joinable()) pu.join();
	else cout << "Error!\n"; 
	if (po.joinable())	po.join();
	else cout << "Error!\n";

	//create 3 persons who want to make a call from call box
	thread person1(make_a_call);
	thread person2(make_a_call);
	thread person3(make_a_call);
	if (person1.joinable())
	{
		person1.join();
	}
	if (person2.joinable())
	{
		person2.join();
	}
	if (person3.joinable())
	{
		person3.join();
	}
	return 0;
}
