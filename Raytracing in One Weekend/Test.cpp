#include <iostream>
#include "vec3.h"

using namespace std;

int main() {
	vec3 vec1(4, 5, 6);
	vec3 vec2(1, 2, 3);

	vec3 newVec;
	newVec = vec1 * vec2;

	cout << newVec.getX() << ' ' << newVec.getY() << ' ' << newVec.getZ() << endl;

	return 0;
}