/*
 * Line3D.h
 *
 *  Created on: 20 août 2024
 *      Author: esn
 */

#ifndef LINE3D_H_
#define LINE3D_H_

#include "Point3D.h"
#include "../utilities/functions.h"
#include "../utilities/Printable.h"

/*
 * ##########
 *  Line3D :)
 * ##########
 * A line is represented by two points.
 * This class present a few useful methods
 * to compute the geometry of the objects.
 */
class Line3D : public Printable {
protected:
	Point3D<float, char>* m_pp1;
	Point3D<float, char>* m_pp2;
	bool m_delp1;
	bool m_delp2;

public:
	Line3D();
	Line3D(const Point3D<float, char>& p1, const Point3D<float, char>& p2);
	Line3D(Point3D<float, char>* pp1, Point3D<float, char>* pp2);
	Line3D(const Line3D& l);
	Line3D(const Line3D* pl);
	virtual ~Line3D();												//:)

	Point3D<float, char> getP1() const;								//:)
	Point3D<float, char>* getPP1() const;							//:)
	void setP1(Point3D<float, char>& p1, const bool& delp=false);	//:)
	void setPP1(Point3D<float, char>* pp1, const bool& delp=true);	//:)
	Point3D<float, char> getP2() const;								//:)
	Point3D<float, char>* getPP2() const;							//:)
	void setP2(Point3D<float, char>& p2, const bool& delp=false);	//:)
	void setPP2(Point3D<float, char>* pp2, const bool& delp=true);	//:)
	bool getDelP1() const;											//:)
	bool getDelP2() const;											//:)

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
};


#endif /* LINE3D_H_ */
