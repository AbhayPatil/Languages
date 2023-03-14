//
// The 'blocking_queue' is a thread-safe.
//
// The 'producer' thread produces an integer after every 'producer_interval'
// milliseconds.
//
// The 'consumer_odd' thread consumes an odd integer after every
// 'consumer_odd_interval' milliseconds.
//
// The 'consumer_even' thread consumes an even integer after every
// 'consumer_even_interval' milliseconds.
//

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

using namespace std;

enum NumType { EVEN, ODD };

template <typename E> class blocking_queue {
private:
  queue<E> _queue;

  mutex _mtx;
  condition_variable _cond;

  bool *done;
  int _max_size;

public:
  blocking_queue(int max_size, bool *done_in) : _max_size(max_size) {
    done = done_in;
  }

  void push(E e) {
    unique_lock<mutex> lock(_mtx);

    // To ensure that the queue size never exceeds _max_size.
    _cond.wait(lock, [this]() { return _queue.size() < _max_size; });

    _queue.push(e);

    lock.unlock();
    _cond.notify_all();
  }

  E pop(NumType nt) {
    unique_lock<mutex> lock(_mtx);

    // To ensure that queue is read only if it is non empty.
    _cond.wait(lock, [this]() { return !_queue.empty() || *done; });

    E item = _queue.front();

    // Only pop if the correct consumer (odd/even) is calling pop().
    int rem = (nt == ODD) ? 1 : 0;
    if (item % 2 != rem || _queue.empty()) {
      _cond.notify_all();
      return -1;
    }
    _queue.pop();

    _mtx.unlock();
    _cond.notify_all();
    return item;
  }

  bool isEmpty() {
    lock_guard<mutex> m(_mtx);
    return _queue.empty();
  }
};

int main() {
  bool done = false;

  blocking_queue<int> qu(5, &done);

  int producer_interval = 1;
  int consumer_odd_interval = 2;
  int consumer_even_interval = 3;

  int even_consumed = 0;
  int odd_consumed = 0;
  int nums_produced = 0;

  thread consumer_even([&]() {
    while (true) {
      if (done && qu.isEmpty())
        break;
      this_thread::sleep_for(chrono::milliseconds(consumer_even_interval));
      auto item = qu.pop(EVEN);
      if (item != -1) {
        // cout << "Even consumed " << item << endl;
        even_consumed++;
      }
    }
  });

  thread consumer_odd([&]() {
    while (true) {
      if (done && qu.isEmpty())
        break;
      this_thread::sleep_for(chrono::milliseconds(consumer_odd_interval));
      auto item = qu.pop(ODD);
      if (item != -1) {
        // cout << "Odd consumed " << item << endl;
        odd_consumed++;
      }
    }
  });

  thread producer([&]() {
    for (int i = 0; i < 25; i++) {
      this_thread::sleep_for(chrono::milliseconds(producer_interval));
      qu.push(i);
      // cout << "Added " << i << endl;
      nums_produced++;
    }
    done = true;
  });

  producer.join();
  consumer_even.join();
  consumer_odd.join();

  cout << "Total even consumed: " << even_consumed << endl;
  cout << "Total odd consumed: " << odd_consumed << endl;
  cout << "Total nums produced: " << nums_produced << endl;

  return 0;
}
