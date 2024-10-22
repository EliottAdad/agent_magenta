/*
 * Figure3D.h
 *
 *  Created on: 20 mai 2024
 *      Author: esn
 */

#ifndef FIGURE3D_H_
#define FIGURE3D_H_

#include <unordered_set>
#include "../core/Point3D.h"
#include "../utilities/Printable.h"

/*
 * ############
 *  Figure3D :)
 * ############
 */
class Figure3D : public Printable {
protected:
	std::unordered_set<Point3D*> m_ppoints;
public:
	Figure3D();
	virtual ~Figure3D();
	Figure3D(const Figure3D &other);

	std::unordered_set<Point3D*> setPoint(Point3D* ppoint);
	void setPPoint(Point3D* ppoint);

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned int& indent=0) const;
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned int& indent=0) const;
};

#endif /* FIGURE3D_H_ */
