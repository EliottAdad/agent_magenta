/*
 * VectorField.hpp
 *
 *  Created on: 9 mai 2024
 *      Author: esn
 */

#ifndef VECTORFIELD_HPP_

#define VECTORFIELD_HPP_


#include <memory>
#include <vector>
#include <unordered_set>
#include <iostream>

//#include "Particle3DSet.hpp"
#include "TimeSensitive.hpp"
#include "../utilities/Printable.hpp"


/*
 * ###############
 *  VectorField :)
 * ###############
 * Uses the weights of the particles.
 */
/*template <typename T> */
class VectorField : public TimeSensitive {
protected:
	// @TODO change mode to integer where it indicates the degree of differenciation (acc, jerks, ...) no speed or displacement
	unsigned char m_mode;										// Indication about whether it should be applied to the particles as acceleration('a'), jerk('j') or displacement('d').
	float m_k;													// Coeff of proportionnality to apply.
	std::unordered_set<TimeSensitive*> m_pmoveables;					// Pointers to the TimeSensitives.

public:
	VectorField();
	//VectorField(std::unordered_set<Particle3D*>* pparts);
	virtual ~VectorField();
	VectorField(const VectorField &other);

	std::unordered_set<TimeSensitive*> getPMoveables() const;
	bool addPMoveable(TimeSensitive* pmoveable);
	unsigned char getMode() const;
	void setMode(const unsigned char& mode);

	/*virtual void applyAsAcc(const float& dt);
	virtual void applyAsSpeed();
	virtual void applyAsPos();*/
	virtual void setT(const float& dt);//Apply given the mode (a, j, p)

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)

};

#endif /* VECTORFIELD_HPP_ */
