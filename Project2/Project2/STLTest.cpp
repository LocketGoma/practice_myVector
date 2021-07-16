// STLTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include "CMyVector.h"
#include <vector>
//#include "Ptr.h"

//#ifdef _DEBUG
//
//#define _CRTDBG_MAP_ALLOC
//#include <cstdlib>
//#include <crtdbg.h>
//
//
//void DetectLeak(long goToLine = -1)
//{
//    //Also need this for memory leak code stuff
//    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//    _CrtSetBreakAlloc(goToLine); //Important!
//}
//
//#endif // _DEBUG

class Foo
{
public:
    Foo() : i(0) { std::cout << "constructor" << std::endl; }
    explicit Foo(int i) : i(i) { std::cout << "constructor" << std::endl; }
    explicit Foo(int i, int* count) : i(i), count(count) { std::cout << "constructor" << std::endl; }
    Foo(const Foo& foo) : Foo(foo.i, foo.count) { std::cout << "copy constructor" << std::endl; }
    Foo(Foo&& foo) noexcept : Foo(foo.i, foo.count) { std::cout << "move constructor" << std::endl; }
    ~Foo() { std::cout << "destructor" << (*count)++ << std::endl; }

    void func() { std::cout << (*count)++ << temp << std::endl; }

private:
    int i;
    int* count = nullptr;
    std::string temp = "hello";
};

template<typename T>
std::ostream& operator<<(std::ostream& s, const vector<T>& v)
{
    s.put('[');
    char comma[3] = { '\0', ' ', '\0' };
    for (const auto& e : v) {
        s << comma << e;
        comma[0] = ',';
    }
    return s << ']';
}
//
//int mainA()
//{
//#ifdef _DEBUG
//    //DetectLeak();
//#endif // _DEBUG
//
//    std::cout << "Test int constructor" << std::endl;
//    CMyVector<int> int1{ 1, 2, 3, 4, 5 };
//
//    std::cout << std::endl;
//    std::cout << "Test user-defined class constructor" << std::endl;
//    int count = 0;
//    CMyVector<Foo> foo(5, Foo(2, &count));
//    foo[0].func();
//
//    // Test constructor
//    // c++11 initializer list syntax:
//    std::cout << std::endl;
//    CMyVector<std::string> words1{ "the", "frogurt", "is", "also", "cursed" };
//    std::cout << "words1: " << words1 << '\n';
//
//    std::cout << std::endl;
//    // words2 == words1
//    CMyVector<std::string> words2(words1.begin(), words1.end());
//    std::cout << "words2: " << words2 << '\n';
//
//    std::cout << std::endl;
//    // words2 == words1
//    //vector<std::string> rwords2(words1.rbegin(), words1.rend());
//    std::cout << "words2: " << words2 << '\n';
//
//    std::cout << std::endl;
//    // words3 == words1
//    vector<std::string> words3(words1);
//    std::cout << "words3: " << words3 << '\n';
//
//    std::cout << std::endl;
//    // words4 is {"Mo", "Mo", "Mo", "Mo", "Mo"}
//    vector<std::string> words4(5, "Mo");
//    std::cout << "words4: " << words4 << '\n';
//
//    std::cout << std::endl;
//    words4.emplace(words4.begin() + 2, "emplace", "emplace2");
//    words4.emplace(words4.cbegin() + 1, "emplac3");
//    words4.emplace_back("emplace_back", "emplace_back2");
//    words4.push_back("push_back");
//    words4.insert(words4.cbegin() + 5, "insert_at_index_5");
//    std::cout << "words4: " << words4 << '\n';
//
//    std::cout << std::endl;
//    std::cout << "pop back" << '\n';
//    words4.pop_back();
//    std::cout << "words4: " << words4 << '\n';
//
//    std::cout << std::endl;
//    std::cout << "erase 0th index" << '\n';
//    words4.erase(words4.cbegin());
//    std::cout << "words4: " << words4 << '\n';
//
//    std::cout << std::endl;
//    std::cout << "erase 1st to 2nd index" << '\n';
//    words4.erase(words4.cbegin() + 1, words4.cbegin() + 3);
//    std::cout << "words4: " << words4 << '\n';
//
//    std::cout << std::endl;
//    std::cout << "resize to 5" << '\n';
//    words4.resize(5);
//    std::cout << "words4: " << words4 << '\n';
//
//    std::cout << std::endl;
//    std::cout << "resize to 10 with value \"hello\"" << '\n';
//    words4.resize(10, "hello");
//    std::cout << "words4: " << words4 << '\n';
//
//    std::cout << std::endl;
//    std::cout << "clear words1" << '\n';
//    words1.clear();
//    std::cout << "words1: " << words1 << '\n';
//
//    std::cout << std::endl;
//    std::cout << "swap words2 and words4" << '\n';
//    std::cout << "before:" << '\n';
//    std::cout << "words2: " << words2 << '\n';
//    std::cout << "words4: " << words4 << '\n';
//    words2.swap(words4);
//    std::cout << "after:" << '\n';
//    std::cout << "words2: " << words2 << '\n';
//    std::cout << "words4: " << words4 << '\n';
//
//    std::cout << std::endl;
//    std::cout << "destructors of user-defined class when terminate" << '\n';
//
//    return 0;
//}
//
