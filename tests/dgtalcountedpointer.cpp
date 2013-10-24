#include <DGtal/base/CountedPtr.h>
using namespace std;
using namespace DGtal;

unsigned int nb_created;
unsigned int nb_descructed;
struct Test
{

    Test()
    {
        cout << "[" << this << "] constructor" << endl;
        nb_created++;
    }

    Test(const Test& test)
    {
        cout << "[" << this << "] copy constructor" << endl;
        nb_created++;
    }

    virtual ~Test()
    {
        cout << "[" << this << "] destructor" << endl;
        nb_descructed++;
    }

    void operator=(Test& test) {
        cout << "[" << &test << "]=>[" << this << "] assignement" << endl;
    }
};

typedef CountedPtr<Test> TestPointer;

TestPointer return_test_pointer()
{
    return TestPointer(new Test());
}

int main(int argc, char* argv[])
{
    nb_created = 0;
    nb_descructed = 0;
    {
        TestPointer test_pointer_00;
        {
            TestPointer test_pointer_01 = TestPointer(new Test());
            test_pointer_00 = test_pointer_01;
        }

        {
            TestPointer test_pointer_02 = return_test_pointer();
            test_pointer_00 = test_pointer_02;
        }

        {
            Test test_03;
            TestPointer test_pointer_03 = TestPointer(new Test(test_03));
            *test_pointer_00 = test_03;
        }
    }
    cout << nb_created << "/" << nb_descructed << " " << ((nb_created-nb_descructed == 0) ? "OK" : "ERR") << endl;

    return 0;
}

