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
#include "../display/Displayable.h"

/*
 * ####################
 *  Particle3D<M, E> :)
 * ####################
 * A weighted point with a speed.
 */
class Particle3D : public WeightedPoint3D<float, char>, public TimeSensitive, public Displayable {
protected:
	Vector3D* m_ps;// Necessary or else we cannot know where the particle will move if no forces are present (2nd Newton law).
	bool m_dels;
	long double m_dt;

public:
	Particle3D();
	Particle3D(const Point3D<float, char>& p);
	Particle3D(const SN<float, char>& x, const SN<float, char>& y, const SN<float, char>& z);
	Particle3D(const WeightedPoint3D<float, char>& wp);
	Particle3D(const Point3D<float, char>& p, const Vector3D& speed);
	Particle3D(const WeightedPoint3D<float, char>& wp, const Vector3D& speed);
	virtual ~Particle3D();

	virtual SN<float, char> getX() const;
	virtual SN<float, char> getY() const;
	virtual SN<float, char> getZ() const;

	Vector3D getSpeed() const;
	Vector3D* getPSpeed();
	void setSpeed(const Vector3D& v);
	void setSpeed(const Point3D<float, char>& p);
	void addSpeed(const Vector3D& ds);
	void addSpeed(const Point3D<float, char>& p);

	virtual void addAsForce(const Vector3D& v, const long double& dt);
	virtual void addAsAcc(const Vector3D& v, const long double& dt);
	virtual void addAsSpeed(const Vector3D& v);
	virtual void addAsPos(const Vector3D& v);

	virtual void setT(const long double& dt);
	virtual void apply();

	std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
	void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;
};



#endif /* PARTICLE3D_H_ */
