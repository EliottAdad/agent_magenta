/*
 * Triangle3D.h
 *
 *  Created on: 20 mai 2024
 *      Author: esn
 */

#ifndef TRIANGLE3D_H_

#define TRIANGLE3D_H_

#include <memory>

#include "../core/Point3D.h"
#include "Shape3D.h"

/*
 * ##############
 *  Triangle3D :)
 * ##############
 */
template<typename M, typename E> class Triangle3D : public Shape3D {
public:
	std::shared_ptr<Point3D<M, E>> pp1;
	std::shared_ptr<Point3D<M, E>> pp2;
	std::shared_ptr<Point3D<M, E>> pp3;

	Triangle3D();
	Triangle3D(const Point3D<M, E>& p1, const Point3D<M, E>& p2, const Point3D<M, E>& p3);
	Triangle3D(Point3D<M, E>* pp1, Point3D<M, E>* pp2, Point3D<M, E>* pp3);
	virtual ~Triangle3D();
	Triangle3D(const Triangle3D &other);

//	Point3D<M, E> getP1() const;					//
//	Point3D<M, E>* getPP1();					//
//	void setP1(const Point3D<M, E>& p1);		//
//	Point3D<M, E> getP2() const;					//
//	Point3D<M, E>* getPP2();					//
//	void setP2(const Point3D<M, E>& p2);		//
//	Point3D<M, E> getP3() const;					//
//	Point3D<M, E>* getPP3();					//
//	void setP3(const Point3D<M, E>& p3);		//

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
};

#endif /* TRIANGLE3D_H_ */
