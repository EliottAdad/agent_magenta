/*
 * Triangle3D.h
 *
 *  Created on: 20 mai 2024
 *      Author: esn
 */

#ifndef TRIANGLE3D_H_
#define TRIANGLE3D_H_

#include "../core/Point3D.h"
#include "Shape3D.h"

/*
 * ##############
 *  Triangle3D :)
 * ##############
 */
class Triangle3D : public Shape3D {
protected:
	Point3D<float, char>* pp1;
	Point3D<float, char>* pp2;
	Point3D<float, char>* pp3;

	bool m_delP1;
	bool m_delP2;
	bool m_delP3;

public:
	Triangle3D();
	Triangle3D(const Point3D<float, char>& p1, const Point3D<float, char>& p2, const Point3D<float, char>& p3);
	Triangle3D(Point3D<float, char>* pp1, Point3D<float, char>* pp2, Point3D<float, char>* pp3);
	virtual ~Triangle3D();
	Triangle3D(const Triangle3D &other);

	Point3D<float, char> getP1() const;					//
	Point3D<float, char>* getPP1();					//
	void setP1(const Point3D<float, char>& p1);		//
	Point3D<float, char> getP2() const;					//
	Point3D<float, char>* getPP2();					//
	void setP2(const Point3D<float, char>& p2);		//
	Point3D<float, char> getP3() const;					//
	Point3D<float, char>* getPP3();					//
	void setP3(const Point3D<float, char>& p3);		//

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
};

#endif /* TRIANGLE3D_H_ */
