/*
 * LSN.h
 *
 *  Created on: 7 mai 2024
 *      Author: esn
 */

#ifndef LSN_H_

#define LSN_H_

//#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <string>
#include "../utilities/functions.h"
#include "../utilities/Printable.h"

/*
 * #######
 *  LSN :)
 * #######
 * Long Scientific Number
 * It allows to store bigger numbers
 * under scientific notation.
 * Some of the operators with long doubles are broken
 */
struct LSN : public Printable {
	long double m;						// Mantissa
	long int e;						// Exponent

	LSN();
	LSN(const long double& m, const long int& e);

	void recal();												//:)

	long double to_long_double() const;							//:)
	void operator=(const LSN& nb);								//:)
	void operator=(const long double& nb);						//:)
	void operator+=(const LSN& nb);								//:)
	void operator+=(const long double& nb);						//:)
	void operator-=(const LSN& nb);								//:)
	void operator-=(const long double& nb);						//:)
	void operator*=(const LSN& nb);								//:)
	void operator*=(const long double& nb);						//:)
	void operator/=(const LSN& nb);								//:)
	void operator/=(const long double& nb);						//:)

	std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
	void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
};

bool operator==(const LSN& nb1, const LSN& nb2);				//:)
bool operator!=(const LSN& nb1, const LSN& nb2);				//:)
bool operator!=(const LSN& nb1, const long double& nb2);		//:)
bool operator!=(const long double& nb1, const LSN& nb2);		//:)
bool operator<=(const LSN& nb1, const LSN& nb2);				//:)
bool operator<=(const LSN& nb1, const long double& nb2);		//:)
bool operator<=(const long double& nb1, const LSN& nb2);		//:)
bool operator>=(const LSN& nb1, const LSN& nb2);				//:)
bool operator>=(const LSN& nb1, const long double& nb2);		//:)
bool operator>=(const long double& nb1, const LSN& nb2);		//:)
bool operator<(const LSN& nb1, const LSN& nb2);					//:)
bool operator<(const LSN& nb1, const long double& nb2);			//:)
bool operator<(const long double& nb1, const LSN& nb2);			//:)
bool operator>(const LSN& nb1, const LSN& nb2);					//:)
bool operator>(const LSN& nb1, const long double& nb2);			//:)
bool operator>(const long double& nb1, const LSN& nb2);			//:)

LSN operator+(const LSN& nb1, const LSN& nb2);					//:)
LSN operator+(const LSN& nb1, const long double& nb2);			//:)
LSN operator+(const long double& nb1, const LSN& nb2);			//:)
LSN operator-(const LSN& nb1, const LSN& nb2);					//:)
LSN operator-(const LSN& nb1, const long double& nb2);			//:)
LSN operator-(const long double& nb1, const LSN& nb2);			//:)
LSN operator*(const LSN& nb1, const LSN& nb2);					//:)
LSN operator*(const LSN& nb, const long double& k);				//:)
LSN operator*(const long double& k, const LSN& nb);				//:)
LSN operator/(const LSN& nb1, const LSN& nb2);					//:)
LSN operator/(const LSN& nb, const long double& k);				//:)
LSN operator/(const long double& k, const LSN& nb);				//:)

LSN abs(const LSN& nb);											//:)
LSN pow(const LSN& nb, const long int& exp);					//:)
LSN nrt(const LSN& nb, const long int& rt);
LSN sqrt(const LSN& nb);


#endif /* LSN_H_ */
