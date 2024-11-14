/*
 * VectorField.h
 *
 *  Created on: 9 mai 2024
 *      Author: esn
 */

#ifndef VECTORFIELD_H_
#define VECTORFIELD_H_


#include <vector>
#include <unordered_set>
#include <iostream>

//#include "Particle3DSet.h"
#include "Moveable.h"
#include "TimeSensitive.h"
#include "Moveable.h"
#include "../utilities/Printable.h"


/*
 * ###############
 *  VectorField :)
 * ###############
 * Uses the weights of the particles.
 */
/*template <typename T> */
class VectorField: public TimeSensitive {
protected:
	// @TODO change mode to integer where it indicates the degree of differenciation (acc, jerks, ...) no speed or displacement
	unsigned int m_mode;										// Indication about whether it should be applied to the particles as acceleration('a'), jerk('j') or displacement('d').
	float m_k;													// Coeff of proportionnality to apply.
	std::unordered_set<Moveable*> m_pmoveables;					// Pointers to the Moveables.

public:
	VectorField();
	//VectorField(std::unordered_set<Particle3D*>* pparts);
	virtual ~VectorField();
	VectorField(const VectorField &other);

	std::unordered_set<Moveable*> getPMoveables() const;
	bool addPMoveable(Moveable* pmoveable);
	unsigned int getMode() const;
	void setMode(const unsigned int& mode);

	/*virtual void applyAsAcc(const double& dt);
	virtual void applyAsSpeed();
	virtual void applyAsPos();*/
	virtual void setT(const long double& dt);//Apply given the mode (a, j, p)

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned int& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned int& indent=0) const;// :)

};

#endif /* VECTORFIELD_H_ */
