#include "Frustum.h"
namespace Math {

	void Frustum::setFromMatrix(const Matrix4D& matrix)
	{
		double me0 = matrix[0], me1 = matrix[1], me2 = matrix[2], me3 = matrix[3];
		double me4 = matrix[4], me5 = matrix[5], me6 = matrix[6], me7 = matrix[7];
		double me8 = matrix[8], me9 = matrix[9], me10 = matrix[10], me11 = matrix[11];
		double me12 = matrix[12], me13 = matrix[13], me14 = matrix[14], me15 = matrix[15];

		_planes[0].setComponents(me3 - me0, me7 - me4, me11 - me8, me15 - me12);
		_planes[0].normalize();
		_planes[1].setComponents(me3 + me0, me7 + me4, me11 + me8, me15 + me12);
		_planes[1].normalize();
		_planes[2].setComponents(me3 + me1, me7 + me5, me11 + me9, me15 + me13);
		_planes[2].normalize();
		_planes[3].setComponents(me3 - me1, me7 - me5, me11 - me9, me15 - me13);
		_planes[3].normalize();
		_planes[4].setComponents(me3 - me2, me7 - me6, me11 - me10, me15 - me14);
		_planes[4].normalize();
		_planes[5].setComponents(me3 + me2, me7 + me6, me11 + me10, me15 + me14);
		_planes[5].normalize();
	}

	bool Frustum::intersectsSphere(const Sphere3D& sphere)
	{		
		Vector3D center = sphere.center();
		double negRadius = -sphere.radius();

		for (int i = 0; i < 6; i++) {

			double distance = _planes[i].distanceToPoint(center);

			if (distance < negRadius) {

				return false;

			}

		}

		return true;
		
	}
}