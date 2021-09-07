#ifndef RAY_H
#define RAY_H

#include "Vector.hpp"
#include "Point.hpp"

#include <vector>

class Ray {
public: 
	struct Point startPoint;
	struct Vector vectorDirection; // normalized?

	Ray(struct Point p, struct Vector v) {
		this->startPoint = p;
		this->vectorDirection = v;
	};

	Ray(struct Point p) {
		this->startPoint = p;
	};

	Ray() {};

	// double calcB(std::vector vec) {
	// 	return (this->vectorDirection.coord[0] * vec[0] +
	// 			this->vectorDirection.coord[1] * vec[1] + 
	// 			this->vectorDirection.coord[2] * vec[2]) * 2;
	// }
};

#endif