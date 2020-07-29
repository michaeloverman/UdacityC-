#include <thread>
#include <iostream>
#include <vector>

void threadFunction() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // simulate work
    std::cout << "Finished work in thread\n";
}

int main() {
	std::cout << "Hello concurrent world from main! Thread id = " << std::this_thread::get_id() << std::endl;
	unsigned int nCores = std::thread::hardware_concurrency();
    std::cout << "This machine supports concurrency with " << nCores << " cores available" << std::endl;
	std::vector<std::thread> threads;


	// create thread
    std::thread t(threadFunction);

    // do something in main()
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // simulate work
    std::cout << "Finished work in main\n";

    // wait for thread to finish
    t.join();

	// create lambdas
    int id = 0; // Define an integer variable

    //auto f0 = []() { std::cout << "ID = " << id << std::endl; }; // Error: 'id' cannot be accessed

    id++;
    auto f1 = [id]() { std::cout << "ID = " << id << std::endl; }; // OK, 'id' is captured by value

    id++;
    auto f2 = [&id]() { std::cout << "ID = " << id << std::endl; }; // OK, 'id' is captured by reference

    //auto f3 = [id]() { std::cout << "ID = " << ++id << std::endl; }; // Error, 'id' may not be modified

    auto f4 = [id]() mutable { std::cout << "ID = " << ++id << std::endl; }; // OK, 'id' may be modified

    // execute lambdas
    f1();
    f2();
    f4();

	// int n = 4; // Num of threads
	// for (int i = 0; i < n; ++i) {
	// 	threads.emplace_back(std::thread([]() {
	// 		while(true) {
	// 			// std::sleep(5)
	// 		}
	// 	}));
	// }

	// // wait for threads to finish before leaving main
	// std::for_each(threads.begin(), threads.end(), [](std::thread &t) {
	// 	t.join();
	// });
	return 0;
}