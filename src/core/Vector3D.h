/*
 * Vector3D.h
 *
 *  Created on: 11 juin 2024
 *      Author: esn
 */

#ifndef VECTOR3D_H_
#define VECTOR3D_H_

#include "Line3D.h"
#include "Point3D.h"

/*
 * ############
 *  Vector3D :)
 * ############
 * Heritage de Line ne marche pas (What ?)
 */
class Vector3D : public Line3D {
public:
	Vector3D();
	Vector3D(const Point3D& p1, const Point3D& p2);
	Vector3D(Point3D* pp1, Point3D* pp2);
	Vector3D(Point3D* pp1, const Point3D& p2);
	Vector3D(const Point3D& p1, Point3D* pp2);
	Vector3D(const Vector3D& v);
	virtual ~Vector3D();//:)

	void setPPoint(Point3D* ppoint, const bool& delp=true);
	void setPoint(Point3D& point, const bool& delp=false);

	LSN getNorm() const;// :)
	void setNorm(const LSN& norm);// :)
	Point3D getOrigin() const;	//:)
	Point3D* getPOrigin() const;	//:)
	void setOrigin(Point3D& origin, const bool& delp=true);	//:)
	void setPOrigin(Point3D* porigin, const bool& delp=false);	//:)
	void addOrigin(const Point3D& dp);	//:)
	Point3D getEnd() const;	//:)
	Point3D* getPEnd() const;	//:)
	void setEnd(Point3D& end, const bool& delp=true);	//:)
	void setPEnd(Point3D* pend, const bool& delp=false);	//:)
	void addEnd(const Point3D& dp);	//:)

	virtual void operator=(const Vector3D& v);// :)
	virtual void operator+=(const Vector3D& v);// :)
	virtual void operator-=(const Vector3D& v);// :)
	virtual void operator*=(const long double& k);// :)
	virtual void operator/=(const long double& k);// :)
	virtual void operator*=(const LSN& k);// :)
	virtual void operator/=(const LSN& k);// :)

	virtual bool operator==(const Vector3D& v) const;// :)
	virtual bool operator<=(const Vector3D& v) const;// :)
	virtual bool operator>=(const Vector3D& v) const;// :)

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
};

Vector3D operator+(const Vector3D& v1, const Vector3D& v2);// :)
Vector3D operator-(const Vector3D& v1, const Vector3D& v2);// :)
Vector3D operator*(const Vector3D& v, const long double& k);// :)
Vector3D operator*(const Vector3D& v, const LSN& k);// :)
Vector3D operator/(const Vector3D& v, const long double& k);// :)
Vector3D operator/(const Vector3D& v, const LSN& k);// :)

//Scalar product
LSN operator*(const Vector3D& v1, const Vector3D& v2);// :)

//Vector product
Vector3D operator^(const Vector3D& v1, const Vector3D& v2);// :)



#endif /* VECTOR3D_H_ */
