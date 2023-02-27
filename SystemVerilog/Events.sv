// Code your testbench here
// or browse Examples
`timescale 1ns/1ps

module test();
  event ev;

  initial begin
    #10ns;
    $display("Start at time: %0t", $time);

    fork
    
      // Thread 1
      begin 
        #50ns ->ev; 
        $display("Event fired at time: %0t", $time);
      end
    
      // Thread 2
      begin 
        #20ns @(ev);
        // #20ns wait(ev.triggered); // did not work in iverilog
        $display("Event caught at time: %0t", $time);
      end
    
    join
    $display("Done time: %0t", $time);
  end

endmodule
