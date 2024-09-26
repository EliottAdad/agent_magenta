/*
 * Camera.h
 *
 *  Created on: 26 sept. 2024
 *      Author: esn
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "Point3D.h"
#include "Vector3D.h"
#include "Mesh3D.h"

/*
 * This camera is a cone directed by a normal
 */
class Camera {
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
	void renderPoint(const Point3D& p) const;

	bool testInFielOfView(const Point3D& p) const;
};

#endif /* CAMERA_H_ */
