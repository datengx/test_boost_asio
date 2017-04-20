#include <memory>
#include <iostream>

class Foo {
public:
    Foo() {
      std::cout << "Foo...\n";
    }
    ~Foo() {
      std::cout << "~Foo...\n";
    }
};

class D {
public:
    void operator()(Foo* p) const {
        std::cout << "Call delete from function object...\n";
        delete p;
    }
};

int main()
{
    // only declare an pointer object without underlying managed object,
    // no instance of object will be created
    {
        std::cout << "constructor with no managed object\n";
        std::shared_ptr<Foo> sh1;
    }

    {
        std::cout << "constructor with object\n";
        std::shared_ptr<Foo> sh2(new Foo);
        std::shared_ptr<Foo> sh3(sh2);
        std::cout << sh2.use_count() << '\n';
        std::cout << sh3.use_count() << '\n';
    }

    {
        std::cout << "constructor with object and deleter\n";
        std::shared_ptr<Foo> sh4(new Foo, D());
        std::shared_ptr<Foo> sh5(new Foo, [](auto p) {
           std::cout << "Call delete from lambda...\n";
           delete p;
        });
    }
}
