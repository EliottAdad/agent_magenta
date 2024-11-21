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
#include <memory>

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

	virtual LSN getX() const;							// :)
	virtual LSN getY() const;							// :)
	virtual LSN getZ() const;							// :)
	virtual Point3D getPosition() const;				// :)

	virtual void operator=(const Point3D& p);			// :)
	virtual void operator=(const LSN& nb);				// :)
	virtual void operator+=(const Point3D& p);			// :)
	virtual void operator+=(const LSN& nb);				// :)
	virtual void operator+=(const long double& nb);		// :)
	virtual void operator-=(const Point3D& p);			// :)
	virtual void operator-=(const LSN& nb);				// :)
	virtual void operator-=(const long double& nb);		// :)
	virtual void operator*=(const LSN& k);				// :)
	virtual void operator*=(const long double& k);		// :)
	virtual void operator/=(const LSN& k);				// :)
	virtual void operator/=(const long double& k);		// :)

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};

bool operator==(const Point3D& p1, const Point3D& p2);		// :)
bool operator!=(const Point3D& p1, const Point3D& p2);		// :)
bool operator<=(const Point3D& p1, const Point3D& p2);		// :)
bool operator>=(const Point3D& p1, const Point3D& p2);		// :)
std::unique_ptr<Point3D> operator+(const Point3D& p1, const Point3D& p2);	// :)
std::unique_ptr<Point3D> operator-(const Point3D& p1, const Point3D& p2);	// :)
std::unique_ptr<Point3D> operator*(const Point3D& p, const LSN& k);			// :)
std::unique_ptr<Point3D> operator*(const LSN& k, const Point3D& p);			// :)
std::unique_ptr<Point3D> operator*(const Point3D& p, const long double& k);	// :)
std::unique_ptr<Point3D> operator*(const long double& k, const Point3D& p);	// :)
std::unique_ptr<Point3D> operator/(const Point3D& p, const LSN& k);			// :)
//Point3D operator/(const LSN& k, const Point3D& p);			// :)
std::unique_ptr<Point3D> operator/(const Point3D& p, const long double& k);	// :)
//Point3D operator/(const long double& k, const Point3D& p);	// :)

/*
 * Functions
 */

/*
 * The type T needs: .to_long_double(), .getX(), .getY(), .getZ() that return LSNs
 */
template <typename T> LSN getDistance(const T& p1, const T& p2) {
	return {sqrt(pow((p1.getX()-p2.getX()).to_long_double(), (long int)2) + pow((p1.getY()-p2.getY()).to_long_double(), (long int)2) + pow((p1.getZ()-p2.getZ()).to_long_double(), (long int)2)), 0};// d=sqrt( (xA-xB)²+(yA-yB)² );
}

LSN getDistance(const Point3D& p1, const Point3D& p2={{0,0},{0,0},{0,0}});

#endif /* POINT3D_H_ */
