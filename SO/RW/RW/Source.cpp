#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <shared_mutex>

using namespace std;

int Processos = 0;
vector<int> numbers;

shared_mutex door;

vector <thread> threads;

void Read(int v)
{
	Processos++;
	shared_lock<shared_mutex>s1(door);
	for (int i = 0; i < 10; i++)
	{
		cout << v << ' ';
		
	}
	cout << endl;
	//cout << "ID: " << this_thread::get_id() << " || Reading..." << endl;
	//cout << "Thread || " << v << " " << numbers.size() << endl;

	Processos--;

}

void Write()
{
	while (true)
	{
		if (Processos == 0)
		{
			unique_lock<shared_mutex> u1(door);
			
			Processos++;
			for (int i = 0; i < 10; i++)
			{
				cout << "ID: " << this_thread::get_id() << " || Writing..." << endl;
				numbers.push_back(i);
			}
			Processos--;
			cout << "ID: " << this_thread::get_id() << " || Done Writing!" << endl;
			return;
		}
	}
}




int main()
{
	threads.emplace_back(Write);

	for (int i = 0, c = 0; i < 100; i++,c++)
	{
		threads.emplace_back(Read, c);
	}
	threads.emplace_back(Write);
	
	for (auto& t : threads)
	{
		t.join();
	}

	return 0;
}