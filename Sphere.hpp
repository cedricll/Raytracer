#ifndef SPHERE_H
#define SPHERE_H


#include <stdlib.h>
#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "Vector.hpp"
#include "Point.hpp"
#include "Ray.hpp"
#include <vector>


class Sphere {
public:
	Sphere(struct Point p, int r) {
		this->centerPoint = p;
		this->radius = r;
	};

	Sphere() {};

	struct Point centerPoint;
	int radius;

	std::vector<double> intersections(Ray r) {
		// std::vector<double> delta;
		struct Vector vectorDelta;
		// delta.push_back(abs(this->centerPoint.coord[2]) + abs(r.startPoint.coord[2]));
		// delta.push_back(abs(this->centerPoint.coord[1]) + abs(r.startPoint.coord[1]));
		// delta.push_back(abs(this->centerPoint.coord[0]) + abs(r.startPoint.coord[0]));
		// delta.push_back(r.startPoint.coord[2] - this->centerPoint.coord[2]);
		// delta.push_back(r.startPoint.coord[1] - this->centerPoint.coord[1]);
		// delta.push_back(r.startPoint.coord[0] - this->centerPoint.coord[0]);

		vectorDelta.coord[0] = r.startPoint.coord[0] - centerPoint.coord[0];
	    vectorDelta.coord[1] = r.startPoint.coord[1] - centerPoint.coord[1];
	    vectorDelta.coord[2] = r.startPoint.coord[2] - centerPoint.coord[2];

		// double b{ (delta[0] * r.vectorDirection.coord[0] +
  //                 delta[1] * r.vectorDirection.coord[1] +
  //                 delta[2] * r.vectorDirection.coord[2]) * 2 };

	    double b{(vectorDelta.coord[0] * r.vectorDirection.coord[0] +
                  vectorDelta.coord[1] * r.vectorDirection.coord[1] +
                  vectorDelta.coord[2] * r.vectorDirection.coord[2]) *
                     2};

		// double c{ (delta[0] * delta[0] +
  //                 delta[1] * delta[1] +
  //                 delta[2] * delta[2]) - (radius * radius) };

	     double c{ (vectorDelta.coord[0] * vectorDelta.coord[0] +
	      			vectorDelta.coord[1] * vectorDelta.coord[1] +
	     			vectorDelta.coord[2] * vectorDelta.coord[2]) -
	     			radius * radius };

		double discriminant{ (b * b) - (4 * c) };

		std::vector<double> distances;

		if (discriminant >= 0) {
			double dist1 = (-b + sqrt(discriminant)) / 2;
			double dist2 = (-b - sqrt(discriminant)) / 2;

			if (dist2 > 0) {
				distances.push_back(dist2);
			}

			if (dist1 > 0) {
				distances.push_back(dist1);
			}
		
		}

		else {
			distances.push_back(0);
		}

		

		return distances;
	};


};

#endif