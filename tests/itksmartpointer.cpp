#include <string>
#include <iostream>
#include <itkSmartPointer.h>
#include <itkLightObject.h>
using namespace std;

struct Test : public itk::LightObject
{
		Test() : itk::LightObject()
		{
				cout << "[" << this << "] constructor" << endl;
		}
		
		Test(const Test& test) : itk::LightObject()
		{
				cout << "[" << this << "] copy constructor" << endl;
		}

		virtual ~Test()
	 	{
				cout << "[" << this << "] destructor" << endl;
		}

		void operator=(Test& test) {
				cout << "[" << &test << "]=>[" << this << "] assignement" << endl;
		}
};

Test::Pointer create_pointer_in_function()
{
		return Test::New();
}

int main(int argc, char* argv[])
{
		Test::Pointer a = Test::New();
		cout << a->GetReferenceCount() << endl;
		{
				Test::Pointer b = a;
				cout << a->GetReferenceCount() << endl;
		}
		cout << a->GetReferenceCount() << endl;


		Test::Pointer e = create_pointer_in_function();
		cout << e->GetReferenceCount() << endl;
		
		return 0;
}


