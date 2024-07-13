#include <iostream>
#include "vec3.h"

using namespace std;

int main() {
	Vec3 vec1(4, 5, 6);
	Vec3 vec2(1, 2, 3);

	Vec3 newVec;
	newVec = vec1 * vec2;

	cout << newVec.getX() << ' ' << newVec.getY() << ' ' << newVec.getZ() << endl;

	return 0;
}