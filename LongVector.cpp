#include "LongVector.h"
#include <cstdlib>
#include "math.h"

using namespace std;

#define SULB (sizeof(unsigned long)<<3)

LongVector::~LongVector()
{
	if (n>0) delete[] data;
	data = NULL;
	n=0;
}

LongVector::LongVector()
{
	size=n=0;
	data=NULL;
}

LongVector::LongVector(int num_bits)
{
	size=num_bits;
	n=size/SULB;
	if (size%SULB>0) n+=1;
	data=new unsigned long [n];
	for(int i=0; i<n; i++) data[i]=0;
}

LongVector::LongVector(const LongVector &v)
{
	if (v.n>0)
	{
		size=v.size;
		n=v.n;
		data=new unsigned long[n];
		for(int i=0; i<n; i++) data[i]=v.data[i];
	}
	else
	{
		size=n=0;
		data=NULL;
	}
}

void LongVector::print()
{
	LongVector tmp = *this;
	bool k;
	for (int i = size-1; i >=0; i--)
	{
		k = tmp[i];
		cout << k;
	}
	cout << endl;
}

void LongVector::printint()
{
	for (int i = 0; i < n; i++)
	{
		cout << data[i]<<" ";
	}
}

void LongVector::set(int k)
{
	data[k / SULB] = data[k / SULB] | 1 << (k % SULB);
}

void LongVector::reset(int k)
{
	data[k / SULB] = data[k / SULB] & ~(1 << (k % SULB));
}

int LongVector::weight()
{
	LongVector tmp = *this;
	int w=0;
	for (int i = 0; i <size; i++)
	{
		if (tmp[i]) w++;
	}
	return w;
}

LongVector& LongVector::operator=(const LongVector &v)
{
	if (n>0 && data!=NULL) {delete[] data; n=size=0; data=NULL;}

	if (v.n>0)
	{
		size=v.size;
		n=v.n;
		data=new unsigned long[n];
		for(int i=0; i<n; i++) data[i]=v.data[i];
	}
	else
	{
		size=n=0;
		data=NULL;
	}
	return *this;	
}

LongVector& LongVector::operator=(const unsigned long &u)
{
	if (n==0) {data=new unsigned long[1]; n=1;}
	data[0]=u;
	for(int i=1; i<n; i++) data[i]=0;
	return *this;	
}

bool LongVector::operator==(const LongVector &v)
{
	if (size!=v.size) return false;
	for(int i=0; i<n; i++)
		if (data[i]!=v.data[i]) return false;
	return true;
}

bool LongVector::operator!=(const LongVector &v)
{
	return (!(*this==v));
}

bool LongVector::operator<(const LongVector &v)
{
	if ((*this&v)==*this) return true;
	return false;
}

bool LongVector::operator[](int index)
{
	if (index>=size) return 0;

	int i=index/SULB;
	int j=index%SULB;

	return (((data[i]>>j)&1)!=0);
}

LongVector LongVector::operator|(const LongVector& v)
{
	LongVector t((size>v.size)?(size):(v.size));

	int m=((n>v.n)?(v.n):(n));
	int mm=((n<v.n)?(v.n):(n));

	for(int i=0; i<m;i++)
		t.data[i]=data[i]|v.data[i];

	if (n>v.n)
	{
		for (int i=m; i<mm; i++)
			t.data[i]=this->data[i];
	}
	else
	{
		for (int i=m; i<mm; i++)
			t.data[i]=v.data[i];
	};

	return t;
};

LongVector LongVector::operator^(const LongVector& v)
{
	LongVector t((size>v.size)?(size):(v.size));

	int m=((n>v.n)?(v.n):(n));
	int mm=((n<v.n)?(v.n):(n));

	for(int i=0; i<m;i++)
		t.data[i]=data[i]^v.data[i];

	if (n>v.n)
	{
		for (int i=m; i<mm; i++)
			t.data[i]=this->data[i];
	}
	else
	{
		for (int i=m; i<mm; i++)
			t.data[i]=v.data[i];
	};

	return t;
};

LongVector LongVector::operator&(const LongVector& v)
{
	LongVector t((size>v.size)?(size):(v.size));

	int m=((n>v.n)?(v.n):(n));
	int mm=((n<v.n)?(v.n):(n));

	for(int i=0; i<m;i++)
		t.data[i]=data[i]&v.data[i];

	for (int i=m; i<mm; i++)
		t.data[i]=0;

	return t;
};

LongVector LongVector::operator~()
{
	LongVector v(*this);
	for(int i=0; i<v.n; i++)
		v.data[i]=~v.data[i];
	return v;
};