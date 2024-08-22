#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "hittable.h"


class Triangle : public Hittable {
public:
	Triangle(const Point3& input_A, const Point3& input_B, const Point3& input_C, shared_ptr<Material> material) {
		m_Vertex0 = input_A;
		m_Vertex1 = input_B;
		m_Vertex2 = input_C;
		m_CurrMaterial = material;
	}

	bool isObjectHit(const Ray& curr_ray, Interval ray_t, HitRecord& record) const override {
		Vec3 A = m_Vertex1 - m_Vertex0;
		Vec3 B = m_Vertex2 - m_Vertex0;
		Vec3 C = getCrossProduct(A, B);		
		Vec3 outward_normal = getUnitVector(C);

		//Set normal to be facing the correct direction; we want normals to point towards incoming ray
		record.setFaceNormal(curr_ray, outward_normal);



		record.m_CurrMaterial = (*this).m_CurrMaterial;

		return false;
	}

private:
	Point3 m_Vertex0;
	Point3 m_Vertex1;
	Point3 m_Vertex2;
	shared_ptr<Material> m_CurrMaterial;
};

#endif