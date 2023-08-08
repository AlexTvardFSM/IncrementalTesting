#include <iostream>
using namespace std;
class LongVector
{
private:
	int size; //number of bits
	int n;//size of data
	unsigned long *data;//vector

public:
	LongVector();
	LongVector(int num_bits);
	LongVector(const LongVector &v);
	~LongVector();

	void print();
	void printint();
	void set(int k);
	void reset(int k);
	int weight();

	LongVector& operator=(const LongVector &v);
	LongVector& operator=(const unsigned long &u);
	bool operator==(const LongVector &v);
	bool operator!=(const LongVector &v);
	bool operator<(const LongVector &v);
	bool operator[](int index);

	LongVector operator|(const LongVector& v);
	LongVector operator^(const LongVector& v);
	LongVector operator&(const LongVector& v);
	LongVector operator~();
};
