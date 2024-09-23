/*
 * Line3D.h
 *
 *  Created on: 20 août 2024
 *      Author: esn
 */

#ifndef LINE3D_H_
#define LINE3D_H_

#include "Point3D.h"
#include "functions.h"
#include "Printable.h"

/*
 * ##########
 *  Line3D :)
 * ##########
 * A line is represented by two points.
 * This class present a few usefull methods
 * to compute the geometry of the objects.
 */
class Line3D : public Printable {
protected:
	Point3D* m_pp1;
	Point3D* m_pp2;
	bool m_delp1;
	bool m_delp2;

public:

	/*:)
	 * By default constructor
	 */
	Line3D();
	Line3D(const Point3D& p1, const Point3D& p2);
	Line3D(Point3D* pp1, Point3D* pp2);
	Line3D(const Line3D& l);
	virtual ~Line3D();//:)

	Point3D getP1() const;	//:)
	Point3D* getPP1();//:)
	Point3D getP2() const;	//:)
	Point3D* getPP2();//:)
	bool getDelP1() const;	//:)
	bool getDelP2() const;	//:)

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned int& indent=0) const;
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned int& indent=0) const;
};


#endif /* LINE3D_H_ */
