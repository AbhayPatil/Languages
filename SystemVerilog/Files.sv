// Strings are not synthesizable.

module files();
  integer fd;
  string content = "Hello";

  initial begin
    fd = $fopen("my_file.txt", "w"); // "r" for read
    if (fd) begin
      $fdisplay(fd, content); // $fget for read
    end
    $fclose(fd);
  end
endmodule
