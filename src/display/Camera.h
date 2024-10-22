/*
 * Camera.h
 *
 *  Created on: 26 sept. 2024
 *      Author: esn
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "../core/Point3D.h"
#include "../core/Vector3D.h"
#include "../geometry/Mesh3D.h"
#include "../geometry/Triangle3D.h"
#include "../utilities/Printable.h"

/*
 * This camera is a cone directed by a normal
 */
class Camera: public Printable {
private:
	float m_aperture;		//Aperture angle in radians
	Point3D* m_ppoint;
	Vector3D* m_pnormal;
	float m_roll_ang;		//Roll angle to the normal
	//m_window;

	bool m_delp;
	bool m_deln;
public:
	Camera();
	virtual ~Camera();
	//Camera(const Camera &other);

	Point3D getPoint() const;
	void setPoint(const Point3D& p);
	//Vector3D* getPNormal();
	Vector3D getNormal() const;
	void setNormal(const Point3D& p);
	Vector3D getE1() const;
	Vector3D getE2() const;

	void renderMesh(const Mesh3D& mesh) const;
	void renderTriangle(const Triangle3D& triangle) const;
	void renderPoint(const Point3D& p) const;

	bool testInFielOfView(const Point3D& p) const;
};

#endif /* CAMERA_H_ */
