#include "node.h"
#include <algorithm> 

using namespace std;


template <typename KDT, typename DDT>
class Map {
private:
	int curr_size = 0; //Used To Keep Track Of The Current Size Of The Array
	int max_size = 2; //Used To Initalise The Array And Keep Track Of Its Max Length
	Node<KDT, DDT>** arrOfData = new Node<KDT, DDT>*[max_size]; //Creates An Array Of Class Pointers 
public:
	Map() {

	};
	~Map() {
		clear();
	};
	//Resize Array If Needed And Inserts Element Into Array If There Is Space. Returns True If Succesful Insert
	bool insert(KDT, DDT);
	//Swaps Two Maps By Storing The Key & Data Of Both Maps And Then Swapping Which Data Gets Inserted Where
	void swap(Map*);
	//Receives A Key As A Paramater And Uses That Key To Remove The Element
	void erase(KDT);
	//Takes Advantage Of Erase Remove By Key As It Cycles Through The First Index And Uses That Key
	void clear();
	//Takes A LowerIndex, HigherIndex and Key. Compares Key to Is_Condition_Match
	int find_if(int, int, KDT);
	//Returns The Address Of A Pointer Found
	Node<KDT, DDT>* find(KDT);
	//Returns The Curr_Size Of The Array
	int size();
	//Returns The Set Max Size Until It Needs Resizing
	int maxSize();
	//Checks Whether Map Is Empty
	bool empty();
	//Compares The Index's Key To The Given Key
	bool is_condition_matched(int, KDT);
	//Returns The First Element
	Node<KDT, DDT>* begin() const;
	//Returns The Last Element
	Node<KDT, DDT>* end() const;
	//Returns The Starting Element But One
	Node<KDT, DDT>* rbegin() const;
	//Returns The End Element But One
	Node<KDT, DDT>* rEnd() const;
};


/*
Insert Method Takes Both The Key And Data And Returns True Or False Depending On Whether The Insert Took Place. At First It Checks Whether The Array Needs To Be
Doubled In Size And If It Does It Doubles The max_size datamember and uses it with a new initalisation of an array of pointers of type Node. Then the contents of the
arrOfData is copied into newArr. The Max_Size data member is changed so the application knows when to increase the size again. The Contents of ArrOfData is deleted before
the content of newArr is added into ArrOfData while ArrOfData is now larger.
In order to promote code reuse the find_if method is used to check whether the incoming Key is already inputted into the map. If it is it throws an exception it is available
an initalisaiton of node is created and it takes in its key and data and it is stored into the arrOfData array at its current size.
*/
template <typename KDT, typename DDT>
bool Map<KDT, DDT>::insert(KDT key, DDT data) {
	try {
		//Makes Sure Size Is Always Smaller Than The Max Size
		if (size() == maxSize() - 1) {
			//Logic To Effectively Double The Size Of The Array 
			size_t newSize = max_size * 2; //Doubles The Max Size
			Node<KDT, DDT>** newArr = new Node<KDT, DDT>*[newSize]; //Places The New Max Size In The Node To Create A Array Of Double Size
			memcpy(newArr, arrOfData, newSize * sizeof(Node<KDT, DDT>*)); //Copys The Array Into The New Now Longer Array
			max_size = newSize; //Changes The Value Of The Max Size So The Object Knows
			delete[] arrOfData; //Deletes The Old Array
			arrOfData = newArr; //Replaces The ArrOfData with contents of newArr
		}
		//Size Would Be The Same As Max Size. Array Needs Size Increasing.
		else {

		}
		//Key Is Already Stored 
		if (find_if(0, size(), key) != -1){
			throw 2;
		}
		//Key Is Not Stored
		else {
			arrOfData[size()] = new Node<KDT, DDT>(key, data); //Adds New Initalisation Of Node To The Array
			curr_size++; //Increments Size Of Array
			return true;
		}

	}
	catch (int e) {
		if (e == 1)
			cout << "Size Is Bigger Than The Max Size. This Shouldn't Happen ERROR:" << e << endl;
		else if (e == 2)
			cout << "Key Is Already Stored ERROR:" << e << endl;
	}
	return false;
}
/*
Clear Method is used to clear all elements of the Map and tihs is achieved by reusing code already implemented such as the empty method and the erase method. This method
uses a while loop which states while the map is not empty go through the arrOfData array and find its return Key value. It is done like this so the application loops through
and removes each element as the returnKey is going to be the first element in the array so using the code built it will be efficient in removing it.
*/
template <typename KDT, typename DDT>
void Map<KDT, DDT>::clear() {
	try {
		Node<KDT, DDT>* pointer;
		while (empty() == false) {
			int i = 0;
			pointer = arrOfData[i];
			erase(pointer->returnKey());
			i++;
		}
	}
	catch (int e) {

	}
}
/*
Swap Method Swaps The Elements Of Both Arrays By Storing The Content Of Each And Clearing Both And Then Inserting The Content Into The Opposite Map.
This Map and the Foreign Map(Map supplied via Parameter). It Creates A Temp Container For Both Map's Key And Data DataMembers. Then The Size Of
Both Maps Is Stored. After That Both Maps Are Cleared And Once Both Maps Are Considered Empty The Map Would Take Its Opposite Maps Original Size And
Data And Insert It Into Its Self Thus Creating Swapped Maps. All Containers Are Deleted Once The Swap Has Taken Place.
*/
template <typename KDT, typename DDT>
void Map<KDT, DDT>::swap(Map* InputMap) {
	try {

		//Temp Key And Data Input For The Foreign Map Container
		KDT* tempKeyInputMapContainer = new KDT[InputMap->size()]; //Stores Temp Key Data
		DDT* tempDataInputMapContainer = new DDT[InputMap->size()]; //Stores Temp Data

		//Temp Key And Data Input For This Map Container
		KDT* tempKeyThisContainer = new KDT[size()]; //Stores Temp Key Data (This Map)
		DDT* tempDataThisContainer = new DDT[size()]; //Stores Temp Data (This Map)

		//Pointer Used To Access ArrOfData Methods
		Node<KDT, DDT>* pointer; //Creates Pointer Of Node

		int tempInputMapSize = InputMap->size(); //Stores Size Of Foreign Map Prior Clear
		int tempThisMapSize = size(); //Stores Size Of This Map Prior Clear

		//Stores Data Of Both Maps
		for (int i = 0; i < tempInputMapSize; i++) {
			//Stores The Data In The Temp Container
			pointer = InputMap->arrOfData[i]; 
			tempKeyInputMapContainer[i] = pointer->returnKey();
			tempDataInputMapContainer[i] = pointer->returnData();
			//Fills Data And Key For Foreign Map By Retrieving Data Via Pointer
		}
		for (int i = 0; i < tempThisMapSize; i++) {
			//Stores The Data In The Temp Container
			pointer = arrOfData[i];
			tempKeyThisContainer[i] = pointer->returnKey();
			tempDataThisContainer[i] = pointer->returnData();
			//Fills Data And Key For This Map By Retrieving Data Via Pointer
		}

		//Deletes The Contents Of The Map
		InputMap->clear();
		clear();

		//Checks That Both Maps Are Empty Before Swapping
		if (InputMap->empty() == true && empty() == true) {

			// (This) Insert Values Of InputMap Key & Data
			int arrayIndex = 0;
			while (arrayIndex < tempInputMapSize) {
				//Inserts Data & Key From Foreign Map To This Map By Going Through Temp Containers
				insert(tempKeyInputMapContainer[arrayIndex], tempDataInputMapContainer[arrayIndex]);
				arrayIndex++;
			}
			int arrayForeignIndex = 0;
			while (arrayForeignIndex < tempThisMapSize) {
				//Inserts Data & Key From This Map To Foreign Map By Going Through Temp Containers
				InputMap->insert(tempKeyThisContainer[arrayForeignIndex], tempDataThisContainer[arrayForeignIndex]);
				arrayForeignIndex++;
			}
		}

		//Deletes Containers Created For Swap
		delete[] tempKeyInputMapContainer;
		delete[] tempDataInputMapContainer;

		delete[] tempKeyThisContainer;
		delete[] tempDataThisContainer;
	}
	catch (int e) {

	}
}
/*
Erase Method Removes A Element By Its Key. This Method Is Achieved By Reusing The Find_If Method And This Returns The Index Of A Key
And If That keyIndex Is Not -1 (-1 Means Invalid, Cannot Be 0 (False) Due To 0 Being An Index Of ArrOfData). If The Key Is Valid
The Find_IF method returns an index and that index will be deleted and then any elements after the deleted element will be moved 
back by one .
*/
template <typename KDT, typename DDT>
void Map<KDT, DDT>::erase(KDT key) {
	try {
		int keyIndex = find_if(0, size(), key);
		if (keyIndex == -1){
			throw 10;
		}
		delete arrOfData[keyIndex];
		for (int j = keyIndex; j < size(); ++j) {
			arrOfData[j] = arrOfData[j + 1];
		}

		curr_size--; //Reduces The Size Of The Array
	}
	catch (int e) {
		if (e == 10){
			cout << "The Key You Entered Was Not Found" << endl;
		}
	}
}
/*
This Template Method Is Used To Compare Any Data Coming Into To It And It Does
This By Using The Index Given With The ArrOfData Array And Using It With A Pointer
In Order To Retrieve Its Return Key And Then Comparing It With The Given Comparison
Parameter. Is Of Boolean Type And Returns True If There Is A Match
*/
template<typename KDT, typename DDT>
bool Map<KDT, DDT>::is_condition_matched(int index, KDT comparison){
	Node<KDT, DDT>* address = arrOfData[index];
	if (address->returnKey() == comparison){
		return true;
	}
	return false;
}
/*
Find_If Method Takes In LowerIndex, UpperIndex And What Is To Be Compared. The Statement Consists
Of Cycling Through The Area And At Each Stage Comparing It With Is_Condition_Matched Method. If A
Match Is Found The Bool Method Will Return True Which Will Initate The Return I Statement In This Method.
If No Match Is Found -1 Is Returned. (Returning Zero Would Make Code Elsewhere Think The Find_If Statement
Is Returning An Element Found At Index Zero)
*/
template <typename KDT, typename DDT>
int Map<KDT, DDT>::find_if(int lowerIndex, int upperIndex, KDT comparison){
	for (int i = lowerIndex; i < upperIndex; i++){
		if (is_condition_matched(i, comparison) == true){
			return i;
		}
	}
	return -1;
}

/*
Reuses The Find_If Method To Retrieve The Index Of A Matched Key. This Method Is Of Node<KDT, DDT>* Type Which
Returns A Pointer So That The Test Application Can Use The Data. If The Index Does Not Equal To -1 (No Key Found)
Use The Index With ArrOfData And A Pointer And Return Its Address.
*/
template <typename KDT, typename DDT>
Node<KDT, DDT>* Map<KDT, DDT>::find(KDT key) {
	try {
		//Retrieves Index
		int index = find_if(0, size(), key);
		if (index != -1){

			Node<KDT, DDT> *pointer = arrOfData[index]; //Uses Index And Sets Pointer To Correct Element Of Array
			return pointer->returnAddress();
		}
		else {
			throw 1;
		}

	}
	catch (int e) {
		if (e == 1)
			cout << "No Key Was Matched. ERROR: " << e << endl;
	}
	return NULL;
}
//Returns The Size Of The Array As An Int
template <typename KDT, typename DDT>
int Map<KDT, DDT>::size() {
	return curr_size;
}
//Returns The Max Size Of The Array As An Int
template <typename KDT, typename DDT>
int Map<KDT, DDT>::maxSize() {
	return max_size;
}
//Returns True If The Map Is Empty
template <typename KDT, typename DDT>
bool Map<KDT, DDT>::empty() {
	if (size() == 0) {
		return true;
	}
	else {
		return false;
	}
}
template <typename KDT, typename DDT>
//Begin Const Iterator. Read Only Iterator To Give Starting Position Of Array.
Node<KDT, DDT>* Map<KDT, DDT>::begin() const {
	return arrOfData[0];
}
template <typename KDT, typename DDT>
//End Const Iterator. Read Only Iterator To Give Ending Position Of Array.
Node<KDT, DDT>* Map<KDT, DDT>::end() const {
	return arrOfData[curr_size - 1];
}
template <typename KDT, typename DDT>
//Reverse Begin Const Iterator. Read Only Iterator To Give Reverse Begin Position Of Array
Node<KDT, DDT>* Map<KDT, DDT>::rbegin() const {
	return arrOfData[1];
}
template <typename KDT, typename DDT>
//Reverse End Const Iterator. Read Only Iterator To Give Reverse End Position Of Array
Node<KDT, DDT>* Map<KDT, DDT>::rEnd() const {
	return arrOfData[size() - 1];
}