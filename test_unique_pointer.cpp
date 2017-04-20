#include <iostream>
#include <memory>

class D;

class Foo {
public:
    Foo() {
      std::cout << "Foo...\n";
    }
    ~Foo() {
      std::cout << "~Foo...\n";
    }
private:
   std::unique_ptr<D> m_d;
};

class D {
public:
    void operator() (Foo* p) {
        std::cout << "Calling delete for Foo object... \n";
        delete p;
    }
};

int main()
{
    std::cout << "Creating an pointer without calling new specifically\n";
    std::unique_ptr<Foo> p1;

    std::cout << "Creating an Foo object\n";
    Foo foo_obj;


    std::cout << "Creating new Foo...\n";
    std::unique_ptr<Foo, D> up(new Foo(), D());  // up owns the Foo pointer (deleter D)

    std::cout << "Replace owned Foo with a new Foo...\n";
    up.reset(new Foo());  // calls deleter for the old one

    std::cout << "Release and delete the owned Foo...\n";
    up.reset(nullptr);
}
