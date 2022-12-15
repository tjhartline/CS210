/*
Created by: Tammy Hartline
Description: Item purchase tracking application
Purpose: Created for CS-210 SNHU Final Project Week7
Version:1.9
Date: 12/11/2022
*/

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>


using namespace std;

string out1 = "         Created by: Tammy Hartline         \n";
string out2 = " CS-210 Programming Languages Final Project \n";
string out3 = "       Now exiting program...Good-bye.      \n";

//I find it easier to replicate and debug formatting that contains more than one line by making the string a variable
string quitOutput = "               " + out1 + "               " + out2 + "               " + out3;


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

//function in C++ to open the file created in Py function to print histogram
void UserOption3() {

	ifstream inputFile;		//define file
	string itemName;		//item names
	int itemCount;			//counts the times item was purchased

	inputFile.open("frequency.dat");	//open file

	//if file was not opened, output error
	if (!inputFile.is_open()) {

		cout << "File: (frequency.dat) was not successfully opened." << endl;

	}
	else {

		//file opened successfully message for testing
		cout << "Successfully opened: (frequency.dat) file." << endl;

	}
	system("cls");	//clear screen
	cout << "|<<<<<<<<<<<<<<<<<<<<<<<< | * | >>>>>>>>>>>>>>>>>>>>>>>>|" << endl;
	cout << "|<<<         Item Purchase History Histogram         >>>|" << endl;
	cout << "|<<<<<<<<<<<<<<<<<<<<<<<< | * | >>>>>>>>>>>>>>>>>>>>>>>>|" << endl << endl;

	while (!inputFile.eof()) {	//while file is opened without error

		inputFile >> itemName;	//read item name from file
		inputFile >> itemCount; //read item count from file
		cout << right;			//align right
		//format display
		cout << setw(20) << itemName << ">>";
		CallProcedure("UserOption3");

		//for loop to calculate frequency of which each item was purchased and outputs like'tally mark' with *
		for (int i = 0; i < itemCount; ++i) {

			cout << "*";

		}

		cout << endl;

	}

	cout << "End of purchase history.";
	cout << endl;
	inputFile.close();		//standard best practice is to close file


}		//end of PrintHistogram() C++ function


int main() {

	//Declare and initialize variables;
	int menuChoice = 0;	//menu input from user
	string itemName;	//item intput from user
	int itemCount;
	int itemReturnValue;	//return int for user based on name entered
	ifstream pyFile;


	//change background color and font color for menu and output to screen found through https://www.geeksforgeeks.org/how-to-print-colored-text-in-c/
	system("Color B0"); //background B = LightAqua | font 0 = black

	CallProcedure("MenuDisplay");	//output menu options
	cout << endl;


	while (menuChoice != 4) {	//will output menu until user enters 4

		pyFile.open("Project3Py");
		cout << endl;
		cout << "                 ";	//move over user input start position
		cin >> menuChoice;				//get users menu selection


		//verify users input is valid
		while (cin.fail()) {

			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Error: your input is invalid. Please enter a number between 1 and 4." << endl;
			cout << "                 ";	//move over user input start position
			cin >> menuChoice;

		}

		//switch statement, directs programs actions based on users input selection
		switch (menuChoice) {

			//case 1: count the number of times each item is in list
		case 1:

			system("cls");	//clear screen before list prints
			CallProcedure("UserOption1");	//call py procedure
			cout << endl;
			break;

			//case 2: count number of times users searched item is purchased and return result
		case 2:


			pyFile.open("Project3Py");
			system("cls");					//clear screen before list prints
			int returnVal;
			callIntFunc("UserOption2", returnVal);
			
			
			

			//case 3: print histogram with number of times of items were purchased
		case 3:

			system("cls");						//clear screen before printing new
			CallProcedure("UserOption3");		//call py procedure to write items to file and print
			UserOption3();
			break;

			//case 4: exit program
		case 4:

			system("cls");
			system("Color 09");
			cout << endl;
			cout << endl;

			cout << quitOutput;

			cout << endl;
			cout << endl;

			return 0;

			//default: tells user the input is invalid
		default:

			system("cls");
			cout << "Invalid Input. Please enter a valid menu selection." << endl;
			CallProcedure("MenuDisplay");	//call menu display
			cout << "                 ";	//move over user input start position
			cin >> menuChoice;
			break;

		}

	}

return 0;

};



