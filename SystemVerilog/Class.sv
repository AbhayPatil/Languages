class AA;
  int p;
  local int q;
  protected int r;
  int x;
  string name;

  task printme(string label = "");
    $display("%s: %s: %0d: %0d, %0d, %0d.", name, label, x, p, q, r);
  endtask

  function new(string name, int x);
    $display("%s: Creating new AA with x = %0d", name, x);
    this.name = name;
    this.x = x;
  endfunction

  task modify_q(int q);
    $display("%s: Modifying q to: %0d", name, q);
    this.q = q;
  endtask

  task modify_r(int r);
    $display("%s: Modifying r to: %0d", name, r);
    this.r = r;
  endtask

endclass

class BB extends AA;
  int y;

  function new(string name, int y);
    super.new(name, y + 1);
    $display("%s: Creating new BB with x = %0d", name, x);
    this.y = y;
  endfunction

endclass

module test ();
  AA a;
  BB b;

  initial begin
    a = new("a", 10);
    a.printme("AfterNew");

    a.p = 20;
    a.printme("AfterP");

    // This does not work as 'q' is local.
    // a.q = 30; 
    a.modify_q(30);
    a.printme("AfterModifyQ");

    // This does not work as 'r' is protected.
    // a.r = 40; 
    a.modify_r(40);
    a.printme("AfterModifyR");

    b   = new("b", 100);
    b.p = 200;
    b.printme("AfterP_in_b");

    // This does not work as 'q' is local.
    // b.q = 300;

    // Ideally following should also not work as q is local 
    // and hence is not visible to derived class. Must investigate more.
    b.modify_q(300);
    b.printme("AfterModifyQ");

    // This does not work as 'r' is protected.
    // b.r = 400; 
    b.modify_r(400);
    b.printme("AfterModifyR");
  end

endmodule
