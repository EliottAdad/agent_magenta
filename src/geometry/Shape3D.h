/*
 * Shape3D.h
 *
 *  Created on: 20 mai 2024
 *      Author: esn
 */

#ifndef SHAPE3D_H_
#define SHAPE3D_H_

#include <unordered_set>
#include "../core/Point3D.h"
#include "../utilities/Printable.h"

/*
 * ###########
 *  Shape3D :)
 * ###########
 */
class Shape3D : public Printable {
protected:
	std::unordered_set<Point3D<float, char>*> m_ppoints;

public:
	Shape3D();
	virtual ~Shape3D();
	Shape3D(const Shape3D &other);

	std::unordered_set<Point3D<float, char>*> setPoint(Point3D<float, char>* ppoint);
	void setPPoint(Point3D<float, char>* ppoint);

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
};

#endif /* SHAPE3D_H_ */
