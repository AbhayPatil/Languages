module test();

  struct packed {
    bit [7:0] red, green, blue;
  } pixel;

  // Following syntax may also work:
  // typedef struct packed {
  //   bit [7:0] red, green, blue;
  // } Pixel;
  //
  // Pixel pixel;

  // Cannot assign packed structure to unpacked 
  // and vice-versa.
  
  // In modern SystemVerilog, the structure is synthesizable if all
  // its members are synthesizable.

  initial begin
    pixel.red = 8'd11;
    pixel.green = 8'hff;

    $display("Red is : %0d\n", pixel.red);
    $display("Red is : %0x\n", pixel.green);
    $display("Pixel is : %0p\n", pixel); // Did not work in iverilog
  end

endmodule
