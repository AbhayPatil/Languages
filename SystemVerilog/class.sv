
class AA;
  int p;
  local int q;
  protected int r;
  int x;

  task printme(string label = "");
    $display("%s: %0d: %0d, %0d, %0d.", label, x, p, q, r);
  endtask

  function new(int x);
    $display("Creating new first: %0d", x);
    this.x = x;
  endfunction

  function modify_q(input int q);
    $display("Modifying q to: %0d", q);
    this.q = q;
    return 1;
    
  endfunction

endclass

//class BB extends AA;
//  int s;
//endclass

module test();
  AA a;
  int xx;

  initial begin
    a = new(1);
    a.printme("AfterNew");
    
    a.p = 22;
    a.printme("AfterP");

    // a.q = 33; This does not work as 'q' is local.
    xx = a.modify_q(33);
    a.printme("AfterModifyQ");

  end
  
endmodule
