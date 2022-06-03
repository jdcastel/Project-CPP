
#include"Streamable.h"
#include<iostream>
using namespace std;
namespace sdds {
	Streamable::~Streamable() {	}

	ostream& operator<<(ostream& os, const Streamable& R_stream) {
		if (R_stream) {
			R_stream.write(os);
		}
		return os;
	}
	istream& operator>>(istream& in, Streamable& R_stream) {
		R_stream.read(in);
		return in;
	}
}