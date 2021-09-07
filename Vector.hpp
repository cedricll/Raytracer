#ifndef VECTOR_H
#define VECTOR_H

#include "Point.hpp"
#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <iostream>

struct Vector {
	double coord[3];

	void vectorBetweenTwoPoints(struct Point p1, struct Point p2) {
		this->coord[0] = p1.coord[0] - p2.coord[0];
		this->coord[1] = p1.coord[1] - p2.coord[1];
		this->coord[2] = p1.coord[2] - p2.coord[2];
	}

	double length() {
		return sqrt(this->coord[0] * this->coord[0] +
					this->coord[1] * this->coord[1] + 
					this->coord[2] * this->coord[2]);
	}

	void normalize() {
		double ray_length = sqrt(this->coord[0] * this->coord[0] +
								this->coord[1] * this->coord[1] + 
								this->coord[2] * this->coord[2]);

		this->coord[0] /= ray_length;
		this->coord[1] /= ray_length;
		this->coord[2] /= ray_length;

	}

	double calcB(struct Vector otherVec) {
		return (this->coord[0] * otherVec.coord[0] +
				this->coord[1] * otherVec.coord[1] + 
				this->coord[2] * otherVec.coord[2]) * 2;
	}

	double calcC(int radius) {
		return (this->coord[0] * this->coord[0] +
				this->coord[1] * this->coord[1] + 
				this->coord[2] * this->coord[2]) - radius * radius;
	}

	void addVector(struct Vector otherVec) {
		this->coord[0] += otherVec.coord[0];
		this->coord[1] += otherVec.coord[1];
		this->coord[2] += otherVec.coord[2];
	}

	void scaleVector(int scalar) {
		this->coord[0] *= scalar;
		this->coord[1] *= scalar;
		this->coord[2] *= scalar;
	}

	int dotProduct(struct Vector otherVec) {
		return this->coord[0] * otherVec.coord[0] +
				this->coord[1] * otherVec.coord[1] + 
				this->coord[2] * otherVec.coord[2];
	}
};

#endif