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
  queue<E> queue_;

  mutex mtx_;
  condition_variable cond_;

  bool done_notify_;
  int max_size_;

  bool consumed_all_elements() { return done_notify_ && queue_.empty(); }

public:
  blocking_queue(int max_size) : max_size_(max_size) { done_notify_ = false; }

  void push(E e) {
    unique_lock<mutex> lock(mtx_);

    // To ensure that the queue size never exceeds max_size_.
    cond_.wait(lock, [this]() { return queue_.size() < max_size_; });

    queue_.push(e);

    lock.unlock();
    cond_.notify_all();
  }

  E pop(NumType nt, bool *consumed_all) {
    unique_lock<mutex> lock(mtx_);

    if (consumed_all_elements()) {
      *consumed_all = true;
    }

    // To ensure that queue is read only if it is non empty.
    cond_.wait(lock, [this]() { return !queue_.empty() || done_notify_; });

    E item = queue_.front();

    // Only pop if the correct consumer (odd/even) is calling pop().
    int rem = (nt == ODD) ? 1 : 0;
    if (item % 2 != rem || queue_.empty()) {
      cond_.notify_all();
      return -1;
    }
    queue_.pop();

    mtx_.unlock();
    cond_.notify_all();
    return item;
  }

  void set_done_notify() {
    lock_guard<mutex> m(mtx_);
    done_notify_ = true;
  }
};

int main() {

  blocking_queue<int> qu(5);

  int producer_interval = 1;
  int consumer_odd_interval = 2;
  int consumer_even_interval = 3;

  int even_consumed = 0;
  int odd_consumed = 0;
  int nums_produced = 0;

  thread consumer_even([&]() {
    bool consumed_all = false;
    while (true) {
      this_thread::sleep_for(chrono::milliseconds(consumer_even_interval));

      auto item = qu.pop(EVEN, &consumed_all);
      if (consumed_all == true)
        break;

      if (item != -1) {
        // cout << "Even consumed " << item << endl;
        even_consumed++;
      }
    }
    cout << "Exiting even consumer thread" << endl;
  });

  thread consumer_odd([&]() {
    bool consumed_all = false;
    while (true) {
      this_thread::sleep_for(chrono::milliseconds(consumer_odd_interval));

      auto item = qu.pop(ODD, &consumed_all);
      if (consumed_all == true)
        break;

      if (item != -1) {
        // cout << "Odd consumed " << item << endl;
        odd_consumed++;
      }
    }
    cout << "Exiting odd consumer thread" << endl;
  });

  thread producer([&]() {
    for (int i = 0; i < 20; i++) {
      this_thread::sleep_for(chrono::milliseconds(producer_interval));

      qu.push(i);

      // cout << "Added " << i << endl;
      nums_produced++;
    }
    qu.set_done_notify();
    cout << "Exiting number producer thread" << endl;
  });

  producer.join();
  consumer_even.join();
  consumer_odd.join();

  cout << endl;
  cout << "Total nums produced: " << nums_produced << endl;
  cout << "Total even consumed: " << even_consumed << endl;
  cout << "Total odd consumed: " << odd_consumed << endl;

  return 0;
}
