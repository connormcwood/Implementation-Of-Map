#include "stdafx.h"
#include "Map.h"

#include <string>
#include <iostream>

template <typename KDT, typename DDT>
/*
This function is called by createInstanceOfMap and this is seperated 
due to this function being able to handle many different datatypes 
due to the templated datatypes. The data types correspond to the Key and Data Datatypes.

This is the area in which the user can test the map.
*/
void createMap(){
	int userinput = 0; //Record The Users Input
	Map<KDT, DDT>* myMap = new Map<KDT, DDT>;

	//Allows The User To Have A Collection Of Commands. Loops Until -1 Or Application Terminated
	while (userinput != -1){
		cout << "What Would You Like To Do With The Map?" << endl;
		cout << "-1. Exit" << endl;
		cout << "0. Insert" << endl; 

		cout << "1. Clear" << endl;
		cout << "2. Erase" << endl;
		cout << "3. Find" << endl;
		cout << "4. Swap" << endl;
		cin >> userinput;

		//Insert Method
		if (userinput == 0){
			int iteration = 0; //Used To count times looped.
			cout << "How Many Elements Would You Like To Add" << endl;
			cin >> userinput;
			
			//Iterates Through The Insert Loop Until The User Types -1 Or Has Completed The Specified Amount Of Inserts
			while (iteration < userinput){				
				KDT keyData;
				DDT dataValue;
				cout << "Type In The Key For This Insert (" << iteration + 1 << ")";
				cin >> keyData;
				cout << "Type In The Data For This Insert" << " (" << iteration + 1 << ")";
				cin >> dataValue;
				cout << endl;
				//Doesn't Add Iteration If Insert Was Not Completed.
				if (myMap->insert(keyData, dataValue)){
					iteration++; //Tallies Amount Of Inserts
				}

			}
		}
		//Clear Method
		else if (userinput == 1){
			myMap->clear();
		}
		//Erase By Key Method
		else if (userinput == 2){
			cout << "What Is The Key You Would Like To Look For And Erase?" << endl;
			KDT keyData;
			cin >> keyData;
			myMap->erase(keyData);
		}
		//Find By Key Method
		else if (userinput == 3){
			cout << "What Is The Key You Would Like To Find?" << endl;
			KDT keyData;
			cin >> keyData;
			if (myMap->find(keyData) != NULL){
				cout << "Data Found Is" << myMap->find(keyData)->returnData() << endl;
			}
		}
		//Swap Method 
		else if (userinput == 4){
			cout << "A Complete Rewrite Would Be Required To Allow Maps Created By User To Be Swapped." << endl;
			cout << "So Instead The Swapped Data Will Already Be PreWritten. Uses Student Key and Student Data." << endl;

			Map<student, student>* StudentMaps = new Map<student, student>;
			StudentMaps->insert(student("Jamal", 1), student("Data", 2));
			StudentMaps->insert(student("Joe", 1), student("Data", 2));
			StudentMaps->insert(student("Jack", 1), student("Data", 2));

			Map<student, student>* Maps = new Map<student, student>;
			Maps->insert(student("Terry", 1), student("Data", 2));
			Maps->insert(student("Test", 1), student("Data", 2));
			Maps->insert(student("John", 1), student("Data", 2));
			Maps->insert(student("Jerry", 1), student("Data", 2));
			Maps->insert(student("Jermaine", 1), student("Data", 2));
			Maps->swap(StudentMaps);
			Maps->clear();
			Maps->~Map();

		}
		//Calls Map Destructor (-1 Ends While Loop)
		else if (userinput == -1){
			myMap->~Map();
		}
	}
}

/*
This function creates an instance of the map and it does this by
asking the user which datatypes they would like to use and corresponds 
the user's input to a map of those specified datatypes 
*/
void createInstanceOfMap(){
	int keyDT, dataDT;
	cout << "What Datatype Would You Like The Key To Be In?" << endl;
	cout << "1. Int" << endl;
	cout << "2. Double" << endl;
	cout << "3. String" << endl;
	cout << "4. Student (Obj)" << endl;
	cin >> keyDT; //Takes In Key DataType
	cout << "What Datatype Would You Like The Data To Be In?" << endl;
	cout << "1. Int" << endl;
	cout << "2. Double" << endl;
	cout << "3. String" << endl;
	cout << "4. Student (Obj)" << endl;
	cin >> dataDT; //Takes In Data DataType

	//Int As Key
	if (keyDT == 1 && dataDT == 1)
		createMap<int, int>();
	else if (keyDT == 1 && dataDT == 2)
		createMap<int, double>();
	else if (keyDT == 1 && dataDT == 3)
		createMap<int, string>();
	else if (keyDT == 1 && dataDT == 4)
		createMap<int, student>();
	//Double As Key
	else if (keyDT == 2 && dataDT == 1)
		createMap<double, int>();
	else if (keyDT == 2 && dataDT == 2)
		createMap<double, double>();
	else if (keyDT == 2 && dataDT == 3)
		createMap<double, string>();
	else if (keyDT == 2 && dataDT == 4)
		createMap<double, student>();
	//String As Key
	else if (keyDT == 3 && dataDT == 1)
		createMap<string, int>();
	else if (keyDT == 3 && dataDT == 2)
		createMap<string, double>();
	else if (keyDT == 3 && dataDT == 3)
		createMap<string, string>();
	else if (keyDT == 3 && dataDT == 4)
		createMap<string, student>();
	//Student As Key
	else if (keyDT == 4 && dataDT == 1)
		createMap<student, int>();
	else if (keyDT == 4 && dataDT == 2)
		createMap<student, double>();
	else if (keyDT == 4 && dataDT == 3)
		createMap<student, string>();
	else if (keyDT == 4 && dataDT == 4)
		createMap<student, student>();
}
int _tmain(int argc, _TCHAR* argv[])
{
	
	//Produces Many Instances Of The Map Depending On How Many The User Would Like
	cout << "How Many Maps Would You Like To Create?" << endl;
	int userInput, index = 0;
	cin >> userInput; //Captures User Input
	while (index < userInput){
		createInstanceOfMap(); //Creates A Instance Of The Map Function
		index++; //Increases Tally Of Total Map
	}

	system("pause");
	return 0;
}

