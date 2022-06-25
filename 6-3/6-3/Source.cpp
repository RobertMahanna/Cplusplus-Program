#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

/*void main()
{
	CallProcedure("printsomething");
	cout << callIntFunc("PrintMe", "House") << endl;
	cout << callIntFunc("SquareValue", 2);

}*/


int main() {
	int userInput = 0;

	// Loop Menu
	do {
		CallProcedure("PrintMenu");
		cin >> userInput;
		/* The following code was adapted from an answer on Stack Overflow. 
			The if statement checks to see if an integer is entered. 
			If one is not cin.fail is true, thus exicuting the if statement.
			The User Input is then reset, the buffer is cleared and the default statment is executed below.
			*/
		if (cin.fail()) {
			userInput = 0; 
			cin.clear(); 
			cin.ignore();
		}
		// Checks User Input and calls right function
		switch (userInput) {

		// Calls Python function to Create a Multiplication Table
		case 1: 
			int numToMult;
			cout << endl << "Enter a number to make a Multiplication Table: ";
			cin >> numToMult;
			cout << endl;
			// Checking if user input is valid
			if (cin.fail()) {
				cout << "Invalid input" << endl << endl;
				userInput = 0;
				cin.clear();
				cin.ignore();
				break;
			}
			cout << "The table for " << numToMult << ":" << endl;
			// I am not using cout below because I do not want to print the return from the Python function
			callIntFunc("MultiplicationTable", numToMult);
			cout << endl;
			break;

		// Calls Python function to Double a Value
		case 2: 
			int numToDouble;
			cout << endl << "Enter a number to double: ";
			cin >> numToDouble;
			cout << endl;
			// Checking if user input is valid
			if (cin.fail()) {
				cout << "Invalid input" << endl << endl;
				userInput = 0;
				cin.clear();
				cin.ignore();
				break;
			}
			cout << numToDouble << " doubled is " << callIntFunc("DoubleValue", numToDouble) << endl << endl;
			break;

		// Exits menu
		case 3:
			cout << "Exiting......" << endl;
			break;

		// Default for invalid user inputs
		default: 
			cout << "Invalid Input" << endl;
			break;
		}
		cout << endl;
	} while (userInput != 3);
}