
module test();

  logic [7:0] memory_1D[15:0];
  logic [7:0] memory_2D[15:0][3:0];

  initial begin

    foreach(memory_1D[i]) begin
      memory_1D[i] = i;
    end
    foreach(memory_1D[i]) begin
      $display("memory_1D[%0d] = %0d", i, memory_1D[i]);
    end


    // Following 2D version did not work in iverilog.
    // Try it out on other simulator.

    // foreach(memory_2D[i, j]) begin
    //   memory_2D[i][j] = i+j;
    // end
    // foreach(memory_2D[i][j]) begin
    //   $display("memory_2D[%0d][%0d] = %0d", i, j, memory_2D[i][j]);
    // end

  end

endmodule
