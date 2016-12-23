#include "student.h"

//Student Constructor Used With 
student::student(string const& inputName, int const& inputGrade)
:name(inputName), averageGrade(inputGrade)
{

}
//Student Constructor Used When There Is No Parameters
student::student(){

}
//A Method Of Student Which Returns Student's Name
string const& student::getName() const {
	return name;
}
//A Method Of Student Which Returns Student's Grade
int const& student::getGrade() const {
	return averageGrade;
}
//A Method Of Student Which Returns Student's Address
student* student::getAddress() {
	return this;
}
//A Method Of Student To Set The Average Grade
void student::setAverageGrade(int studentGrade){
	averageGrade = studentGrade;
}
//A Method Of Student To Set The Name
void student::setName(string studentName){
	name = studentName;
}
//Overloaded Operator Which Allows The Classes Data To Be Displayed
ostream& operator<<(ostream& os, const student& obj) {
	return os << obj.getName() << " " << obj.getGrade();
}
//Overloaded Operator To Allow Data From The User To Be Stored Into The Class
istream& operator>>(istream& is, student& obj) {
	is >> obj.name >> obj.averageGrade;
	return is;
}
//Takes In The Given Value And Compares It To The Objs Actual Real Value For Both Variables
bool operator==(const student& os, const student& obj){
	return (os.getGrade() == obj.getGrade()) && (os.getName() == obj.getName());
}