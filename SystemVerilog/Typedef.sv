`timescale 1ns/1ns

module hw();
  typedef logic [3:0] FourWide;
  FourWide fw;
  
  initial begin
    fw = 4'b1010;
    $display("fw = %b\n", fw);
  end
endmodule
