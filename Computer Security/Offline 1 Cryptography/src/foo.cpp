#include <bits/stdc++.h>
using namespace std;

#include <iostream>

class Foo
{
    string x;

public:
    Foo(char * x) 
    {
        cout<<strlen(x)<<"\n";
        cout<<x<<"\n";
        this->x = x;
    }
    void bar()
    {
        std::cout << "Hello x=" << x << std::endl;
    }
    ~Foo()
    {
        cout<<"Destructor\n";
    }
};

extern "C"
{
    Foo *Foo_new(char * x) { return new Foo(x); }
    void Foo_bar(Foo *foo) { foo->bar(); }
    void Foo_del(Foo * foo) { delete foo; }
}