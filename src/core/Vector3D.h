/*
 * Vector3D.h
 *
 *  Created on: 11 juin 2024
 *      Author: esn
 */

#ifndef VECTOR3D_H_
#define VECTOR3D_H_

#include <memory>

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
	Vector3D(const Point3D<float, char>& p1, const Point3D<float, char>& p2);
	Vector3D(Point3D<float, char>* pp1, Point3D<float, char>* pp2);
	Vector3D(Point3D<float, char>* pp1, const Point3D<float, char>& p2);
	Vector3D(const Point3D<float, char>& p1, Point3D<float, char>* pp2);
	Vector3D(const Vector3D& v);
	Vector3D(const Vector3D* pv);
	virtual ~Vector3D();//:)

	void setPPoint(Point3D<float, char>* ppoint, const bool& delp=true);
	void setPoint(Point3D<float, char>& point, const bool& delp=false);

	SN<float, char> getNorm() const;// :)
	void setNorm(const SN<float, char>& norm);// :)
	Point3D<float, char> getOrigin() const;	//:)
	Point3D<float, char>* getPOrigin() const;	//:)
	void setOrigin(Point3D<float, char>& origin, const bool& delp=true);	//:)
	void setPOrigin(Point3D<float, char>* porigin, const bool& delp=false);	//:)
	void addOrigin(const Point3D<float, char>& dp);	//:)
	Point3D<float, char> getEnd() const;	//:)
	Point3D<float, char>* getPEnd() const;	//:)
	void setEnd(Point3D<float, char>& end, const bool& delp=true);	//:)
	void setPEnd(Point3D<float, char>* pend, const bool& delp=false);	//:)
	void addEnd(const Point3D<float, char>& dp);	//:)

	virtual void operator=(const Vector3D& v);// :)
	virtual void operator+=(const Vector3D& v);// :)
	virtual void operator-=(const Vector3D& v);// :)
	virtual void operator*=(const float& k);// :)
	virtual void operator/=(const float& k);// :)
	virtual void operator*=(const SN<float, char>& k);// :)
	virtual void operator/=(const SN<float, char>& k);// :)

	virtual bool operator==(const Vector3D& v) const;// :)
	virtual bool operator<=(const Vector3D& v) const;// :)
	virtual bool operator>=(const Vector3D& v) const;// :)

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
};

std::unique_ptr<Vector3D> operator+(const Vector3D& v1, const Vector3D& v2);// :)
std::unique_ptr<Vector3D> operator-(const Vector3D& v1, const Vector3D& v2);// :)
std::unique_ptr<Vector3D> operator*(const Vector3D& v, const float& k);// :)
std::unique_ptr<Vector3D> operator*(const Vector3D& v, const SN<float, char>& k);// :)
std::unique_ptr<Vector3D> operator/(const Vector3D& v, const float& k);// :)
std::unique_ptr<Vector3D> operator/(const Vector3D& v, const SN<float, char>& k);// :)

//Scalar product
SN<float, char> operator*(const Vector3D& v1, const Vector3D& v2);// :)

//Vector product
std::unique_ptr<Vector3D> operator^(const Vector3D& v1, const Vector3D& v2);// :)



#endif /* VECTOR3D_H_ */
