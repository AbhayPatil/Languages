#include <chrono>
#include <cmath>
#include <future>
#include <iomanip>
#include <iostream>
#include <thread>

using namespace std;

double return_12345(int terms) {
  this_thread::sleep_for(chrono::milliseconds(3000));
  return 1.2345;
}

int main() {
  promise<double> my_promise;

  auto do_calculation = [&](int terms) {
    auto result = return_12345(terms);
    my_promise.set_value(result);
  };

  thread t1(do_calculation, 1E8);

  // This blocks till my_promise is set inside do_calculation.
  future<double> future = my_promise.get_future();

  cout << setprecision(15) << future.get() << endl;

  t1.join();
  return 0;
}
