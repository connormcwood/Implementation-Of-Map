

#include <string>
using namespace std;

class student {
private:
	string name;
	int averageGrade;

public:
	student(string const&, int const&);
	student();
	string const& getName() const;
	int const& getGrade() const;
	student* getAddress();
	void setName(string);
	void setAverageGrade(int);
	friend istream& operator>>(istream& is, student& obj);
};
ostream& operator<<(ostream& os, const student& obj);
bool operator==(const student& os, const student& obj);