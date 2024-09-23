/*
 * WeightedPoint3D.h
 *
 *  Created on: 14 mai 2024
 *      Author: esn
 */

#ifndef WEIGHTEDPOINT3D_H_
#define WEIGHTEDPOINT3D_H_

#include "Point3D.h"
#include "LSN.h"

/*
 * ###################
 *  WeightedPoint3D :)
 * ###################
 * A point with a weight
 */
struct WeightedPoint3D: public Point3D {
	LSN w;

	WeightedPoint3D();
	WeightedPoint3D(const Point3D& p, const LSN& w={1,0});
	WeightedPoint3D(const LSN& x, const LSN& y, const LSN& z, const LSN& w);
	virtual ~WeightedPoint3D();

	virtual void operator=(const WeightedPoint3D& wp);// :)
	//virtual void operator+=(const Point3D& p);// :)Not necessary
	//virtual void operator-=(const Point3D& p);// :)Not necessary

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned int& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned int& indent=0) const;// :)
};

#endif /* WEIGHTEDPOINT3D_H_ */
