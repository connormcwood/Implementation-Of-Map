using namespace std;
#include <string>
#include "student.h"

template<typename KDT, typename DDT>
class Node {
private:
	KDT key;
	DDT data;
public:

	Node(){

	}
	template<typename KDT, typename DDT>
	Node(KDT inputkey, DDT inputdata)
	{
		setKey(inputkey);
		setData(inputdata);
		cout << this << " Created " << inputkey << "Data: " << data << endl;
	}
	~Node(){
		cout << this << " deleted" << endl;
	}
	void setKey(KDT inputkey){
		key = inputkey;
	}
	void setData(DDT inputdata){
		data = inputdata;
	}
	KDT returnKey(){
		return key;
	}
	DDT returnData(){
		return data;
	}
	Node* returnAddress(){
		return this;
	}

};
template<typename KDT, typename DDT>
bool operator==(const Node<KDT ,DDT>& os, const Node<KDT ,DDT>& obj){
	return os.returnAddress() == obj.returnAddress();
}