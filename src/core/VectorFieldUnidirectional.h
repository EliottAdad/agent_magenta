/*
 * VectorFieldUnidirectional.h
 *
 *  Created on: 18 mai 2024
 *      Author: esn
 */

#ifndef VECTORFIELDUNIDIRECTIONAL_H_
#define VECTORFIELDUNIDIRECTIONAL_H_

#include "Particle3D.h"

#include "Vector3D.h"
#include "VectorField.h"
#include "TimeSensitive.h"

/*
 * #############################
 *  VectorFieldUnidirectional :)
 * #############################
 */
class VectorFieldUnidirectional : public VectorField {
protected:
	Vector3D* m_pv;
	bool m_delv;
public:
	VectorFieldUnidirectional();
	virtual ~VectorFieldUnidirectional();

	Vector3D getVector() const;
	Vector3D* getPVector();

	//virtual void addAsForce(const long double& dt);
	//virtual void addAsAcc(const long double& dt);
	//virtual void addAsSpeed();
	//virtual void addAsPos();

	//virtual void applyAsForce(const long double& dt);
	//virtual void applyAsAcc(const long double& dt);
	//virtual void applyAsSpeed();
	//virtual void applyAsPos();
	virtual void setT(const long double& dt=1);

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned int& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned int& indent=0) const;// :)
};

#endif /* VECTORFIELDUNIDIRECTIONAL_H_ */
