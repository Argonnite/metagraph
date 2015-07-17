#include <iostream.h>

class Chad;

class Howard {
public:
  Howard(Chad& master) : owner(master) {}

  print_master() { cout << &owner << endl; }

private:
  Chad& owner;
};

class Chad {
public:
  Chad() : slave(*this) {}

  Chad(const Chad& c) : slave(*this) {}

  Howard slave;

};



main()
{
  Chad ca;
  cout << &ca << endl;
  ca.slave.print_master();

  Chad cb = ca;
  cout << &cb << endl;
  cb.slave.print_master();

  Chad cc = ca;
  cout << &cc << endl;
  cc.slave.print_master();

}
