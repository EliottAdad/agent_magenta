/*
 * ParticleSystem3D.h
 *
 *  Created on: 7 juin 2024
 *      Author: esn
 */

#ifndef PARTICLESYSTEM3D_H_
#define PARTICLESYSTEM3D_H_

#include <unordered_set>

#include "Particle3D.h"
#include "Oct.h"
#include "TimeSensitive.h"

/*
 * ####################
 *  ParticleSystem3D :)
 * ####################
 * Can contain any object having ->x, ->y or ->z
 */
class ParticleSystem3D: public TimeSensitive {
protected:
	LSN m_a;														// Lenght of the side of the zone
	//std::unordered_set<Particle3D*> m_pparticles;					// Pointers to the Particles (useless: already in the octree)
	Oct<Particle3D>* m_poctree;										// Pointer to the Octree.
	long double m_dt;

public:
	ParticleSystem3D();
	//ParticleSystem3D(const ParticleSystem3D &other);
	virtual ~ParticleSystem3D();

	LSN getA() const;
	/*void setA(const LSN& a);*/
	Oct<Particle3D>* getPOctree();
	//void setOctree(const float& alpha);
	float getAlpha() const;
	void setAlpha(const float& alpha);
	std::unordered_set<Particle3D*> getPParticles() const;
	bool addPParticle(Particle3D* ppart);
	//void removePParticle(Particle3D* ppart);
	//void empty();

	virtual void setT(const long double& dt);	// TimeSensitive
	virtual void apply(const Vector3D& dv);		// Moveable
	//virtual void move(const Vector3D& dp);

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned int& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned int& indent=0) const;// :)
};

/*
 * Returns the vector immediately
 */
Vector3D grav(const Particle3D& p1, const Particle3D& p2);

#endif /* PARTICLESYSTEM3D_H_ */
