/*
 * Moveable.h
 *
 *  Created on: 24 août 2024
 *      Author: esn
 */

#ifndef MOVEABLE_H_

#define MOVEABLE_H_

#include "Vector3D.h"
#include "TimeSensitive.h"
#include "../utilities/Printable.h"

/*
 * Used to show an object can be moved (with speed).(useless, depreciated)
 */
class Moveable : public TimeSensitive {
public:
	Moveable();
	virtual ~Moveable();
	Moveable(const Moveable &other);

	virtual void apply();
	//virtual void apply(const Vector3D& dv);//delta speed to add
	//virtual void applyAsAcc(const Vector3D& v, const long double& dt=1);//Useless, the whole class is useless (jst to be used as an indicator to regroup)
	//virtual void applyAsSpeed(const Vector3D& v);//Useless
	//virtual void applyAsPos(const Vector3D& v);//Useless

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};

#endif /* MOVEABLE_H_ */
