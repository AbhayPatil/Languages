module enum_learn ();
  typedef enum {RED, GREEN, BLUE} Color;
  Color color;

  task Print(Color c);
    //$display("color is: %d or %s\n", color, color.name());
    $display("color is: %d\n", color);
  endtask

  initial begin
    color = GREEN;
    Print(color);

    color = color.last();
    Print(color);
    
    color = color.first();
    Print(color);
    
    color = color.next();
    Print(color);
  end
endmodule
