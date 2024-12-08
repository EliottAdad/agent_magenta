/*
 * Camera.h
 *
 *  Created on: 26 sept. 2024
 *      Author: esn
 */

#ifndef CAMERA_H_

#define CAMERA_H_

#include <memory>

#include "../core/Point3D.h"
#include "../core/Vector3D.h"
#include "../geometry/Mesh3D.h"
#include "../geometry/Triangle3D.h"
#include "../utilities/Printable.h"

/*
 * ##########
 *  Camera :)
 * ##########
 * This camera is a cone directed by a normal
 */
class Camera : public Printable {
private:
	float m_aperture;		//Aperture angle in radians
	std::shared_ptr<Point3D<float, char>> m_ppoint;
	Vector3D* m_pnormal;
	float m_roll_ang;		//Roll angle to the normal
	//m_window;

	//bool m_delp;
	bool m_deln;

public:
	Camera();
	virtual ~Camera();
	//Camera(const Camera &other);

	Point3D<float, char> getPoint() const;
	void setPoint(const Point3D<float, char>& p);
	//Vector3D* getPNormal();
	Vector3D getNormal() const;
	void setNormal(const Point3D<float, char>& p);
	std::unique_ptr<Vector3D> getE1() const;
	std::unique_ptr<Vector3D> getE2() const;

	void renderMesh(const Mesh3D& mesh) const;
	void renderTriangle(const Triangle3D& triangle) const;
	void renderPoint(const Point3D<float, char>& p) const;

	bool testInFielOfView(const Point3D<float, char>& p) const;

	virtual std::string to_string(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
	virtual void print(const bool& spread=false, const bool& full_info=false, const unsigned char& indent=0) const;// :)
};

#endif /* CAMERA_H_ */
