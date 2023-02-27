`timescale 1ns/1ns

module hw();
  logic [3:0] a;
  logic [1:0] b;
  
  task IsUnknown(logic [3:0] in);
    if ($isunknown(a)) $display("a(%b) is unknown\n", a);
    else $display("a(%b) is known\n", a);
  endtask
  
  initial begin
    // a=0;
    // IsUnknown(a); // false

    // a=1'b0;
    // IsUnknown(a); // false

    // a={2'b0};
    // IsUnknown(a); // false

    // b=2'b0;
    // a={b};
    // IsUnknown(a); // false

    a[1:0]=2'b0;
    IsUnknown(a); // true
  end
endmodule
