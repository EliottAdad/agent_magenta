/*
 * Particle3D.h
 *
 *  Created on: 14 mai 2024
 *      Author: esn
 */

#ifndef PARTICLE3D_H_
#define PARTICLE3D_H_

#include "WeightedPoint3D.h"
#include "Vector3D.h"
#include "TimeSensitive.h"

/*
 * ##############
 *  Particle3D :)
 * ##############
 * A weighted point with a speed.
 */
class Particle3D: public WeightedPoint3D, TimeSensitive {
protected:
	Vector3D* m_ps;// Necessary or else we cannot know where the particle will move if no forces are present (2nd Newton law).
	bool m_dels;

public:
	Particle3D();
	Particle3D(const Point3D& p);
	Particle3D(const WeightedPoint3D& wp);
	Particle3D(const Point3D& p, const Vector3D& speed);
	Particle3D(const WeightedPoint3D& wp, const Vector3D& speed);
	virtual ~Particle3D();

	Vector3D getSpeed() const;
	Vector3D* getPSpeed();
	void setSpeed(const Vector3D& v);

	virtual void addAsForce(const Vector3D& v, const long double& dt);
	virtual void addAsAcc(const Vector3D& v, const long double& dt);
	virtual void addAsSpeed(const Vector3D& v);
	virtual void addAsPos(const Vector3D& v);

	std::string to_string(const bool& spread=false, const bool& full_info=false) const;
	void print(const bool& spread=false, const unsigned int& indent=0, const bool& full_info=false) const;
};

#endif /* PARTICLE3D_H_ */
