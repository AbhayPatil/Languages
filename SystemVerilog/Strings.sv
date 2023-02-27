module strings();
  string name = "Abhay";

  initial begin
    $display("String is: %s", name);
    $display("String is: %s", {name, name});
    $display("String is: %s", name.substr(1,2));
    $display("Length of string is: %2d", name.len());
    // $display("String is: %s", name.toupper());
    // $display("String is: %s", name.getc(2));
    // Other supported methods: atoi(), itoa(), 
  end
endmodule
