
// The arrays have other methods that are not shown here.
// size, sum, min, max, unique, ...

module test();

  int dynamic_array[];
  
  // This is actually like C++ deque.
  int queue[$];

  // Acts like a C++ map.
  // Did not compile in iverilog.
  // int associative_array[*];
  
  initial begin
    dynamic_array = new[3];
    dynamic_array[0] = 10;
    dynamic_array[1] = 20;
    dynamic_array[2] = 30;
    
    foreach(dynamic_array[i]) $display("dynamic_array[%0d] = %0d", i, dynamic_array[i]);

    queue.push_back(100);
    queue.push_back(200);
    queue.push_back(300);
    queue.push_front(400);
    // Did not compile in iverilog.
    // queue.pop_back();

    foreach(queue[i]) $display("queue[%0d] = %0d", i, queue[i]);
  end
endmodule
