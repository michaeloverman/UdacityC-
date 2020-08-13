#include <iostream>
#include <random>
#include "TrafficLight.h"

/* Implementation of class "MessageQueue" */

template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait()
    // to wait for and receive new messages and pull them from the queue using move semantics.
    // The received object should then be returned by the receive function.
		std::unique_lock<std::mutex> lock(_mutex);
		// _cond.wait(lock, [this] { return !_queue.empty(); });
		_cond.wait(lock, [this] { return _dataAvailable; }); // per Knowledge suggestion - no change in behavior

		T phase = std::move(_queue.front());
		_queue.pop_front();
		_dataAvailable = false; // per Knowledge suggestion - no change in behavior
		// _queue.clear(); // Suggestion found on Knowledge.... didn't seem to make any difference

		return phase;
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex>
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
	std::lock_guard<std::mutex> lock(_mutex);
	_queue.push_back(std::move(msg));
	_dataAvailable = true; // per Knowledge suggestion - no change in behavior
	_cond.notify_one();
}

/* Implementation of class "TrafficLight" */

TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

void TrafficLight::waitForGreen()
{
    // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop
    // runs and repeatedly calls the receive function on the message queue.
    // Once it receives TrafficLightPhase::green, the method returns.
	// while(true) {
	// 	// TrafficLightPhase ph = _messages.receive();
	// 	if (_messages.receive() == TrafficLightPhase::green) {
	// 		return;
	// 	}
	// }

	// Found on Knowledge - seems to be an improvement, but not universally
    // std::cout << "waitForGreen. lock guard." << std::endl;
    std::lock_guard<std::mutex> lockGuard(_mutex);
    while (true) {
        // std::cout << "waitForGreen. calling receive." << std::endl;
        TrafficLightPhase traffic_phase = _messages.receive();
        // std::cout << "waitForGreen. receive." << traffic_phase << std::endl;
        if (traffic_phase == green) {
            break;
        }
    }
    // std::cout << "waitForGreen. notify one." << std::endl;
    _condition.notify_one();
}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

std::string TrafficLight::getCurrentPhaseString() {
	if (getCurrentPhase() == TrafficLightPhase::green) return "green";
	else return "red";
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    // FP.2a : Implement the function with an infinite loop that measures the time between two loop cycles
    // and toggles the current phase of the traffic light between red and green and sends an update method
    // to the message queue using move semantics. The cycle duration should be a random value between 4 and 6 seconds.
    // Also, the while-loop should use std::this_thread::sleep_for to wait 1ms between two cycles.
	std:srand(std::time(nullptr));
	while (true) {
		int delay = 4000 + std::rand() / (RAND_MAX / 2000);
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		if (_currentPhase == red) _currentPhase = green;
		else _currentPhase = red;
		// notify message queue
		_messages.send(std::move(_currentPhase));

		// 1ms wait between cycles
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void TrafficLight::simulate()
{
	std::cout << "TrafficLight simulate" << std::endl;
    // FP.2b : Finally, the private method „cycleThroughPhases“ should be started in a thread when the public method „simulate“ is called. To do this, use the thread queue in the base class.
	threads.emplace_back(std::thread{ &TrafficLight::cycleThroughPhases, this});
}
