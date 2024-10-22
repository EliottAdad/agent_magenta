/*
 * Point3D.h
 *
 *  Created on: 14 mai 2024
 *      Author: esn
 */

#ifndef POINT3D_H_
#define POINT3D_H_

#include "LSN.h"
#include "../utilities/Printable.h"

/*
 * ###########
 *  Point3D :)
 * ###########
 */
struct Point3D : public Printable {
public:
	LSN x;
	LSN y;
	LSN z;

	Point3D();
	Point3D(const LSN& x, const LSN& y, const LSN& z);
	virtual ~Point3D();
	Point3D(const Point3D& point);//Copy constructor

	virtual void operator=(const Point3D& p);// :)
	virtual void operator=(const LSN& nb);// :)
	virtual void operator+=(const Point3D& p);// :)
	virtual void operator+=(const LSN& nb);// :)
	virtual void operator+=(const long double& nb);// :)
	virtual void operator-=(const Point3D& p);// :)
	virtual void operator-=(const LSN& nb);// :)
	virtual void operator-=(const long double& nb);// :)
	virtual void operator*=(const LSN& k);// :)
	virtual void operator*=(const long double& k);// :)
	virtual void operator/=(const LSN& k);// :)
	virtual void operator/=(const long double& k);// :)

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned int& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned int& indent=0) const;// :)
};

bool operator==(const Point3D& p1, const Point3D& p2);		// :)
bool operator!=(const Point3D& p1, const Point3D& p2);		// :)
bool operator<=(const Point3D& p1, const Point3D& p2);		// :)
bool operator>=(const Point3D& p1, const Point3D& p2);		// :)
Point3D operator+(const Point3D& p1, const Point3D& p2);	// :)
Point3D operator-(const Point3D& p1, const Point3D& p2);	// :)
Point3D operator*(const Point3D& p, const LSN& k);			// :)
Point3D operator*(const LSN& k, const Point3D& p);			// :)
Point3D operator*(const Point3D& p, const long double& k);	// :)
Point3D operator*(const long double& k, const Point3D& p);	// :)
Point3D operator/(const Point3D& p, const LSN& k);			// :)
//Point3D operator/(const LSN& k, const Point3D& p);			// :)
Point3D operator/(const Point3D& p, const long double& k);	// :)
//Point3D operator/(const long double& k, const Point3D& p);	// :)

LSN getDistance(const Point3D& p1, const Point3D& p2={{0,0},{0,0},{0,0}});

#endif /* POINT3D_H_ */
