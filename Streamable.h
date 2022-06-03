
#ifndef SDDS_STREAMABLE_H
#define SDDS_STREAMABLE_H
#include <iostream>

namespace sdds {
	class Streamable {
	public:
		virtual bool conIO(std::ios& io) const = 0;

		virtual std::ostream& write(std::ostream& os) const = 0;
		virtual std::istream& read(std::istream& istr) = 0;

		virtual operator bool() const = 0;

		virtual ~Streamable();
	};
	std::ostream& operator<<(std::ostream& os, const Streamable& R_stream);
	std::istream& operator>>(std::istream& in, Streamable& R_stream);
}
#endif // !SDDS_STREAMABLE_H
