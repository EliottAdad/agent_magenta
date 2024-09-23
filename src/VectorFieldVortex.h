/*
 * VectorFieldVortex.h
 *
 *  Created on: 18 mai 2024
 *      Author: esn
 */

#ifndef VECTORFIELDVORTEX_H_
#define VECTORFIELDVORTEX_H_

#include "VectorField.h"

/*
 * #####################
 *  VectorFieldVortex :)
 * #####################
 */
class VectorFieldVortex : public VectorField {
protected:
	float m_m;				//Moment unit/m or N/m.
	Point3D* m_ppoint;		//Center.
public:
	VectorFieldVortex();
	virtual ~VectorFieldVortex();

	void applyAsForce(const long double& dt);
	void applyAsAcc(const long double& dt);
	void applyAsSpeed();
	void applyAsPos();
};

#endif /* VECTORFIELDVORTEX_H_ */
