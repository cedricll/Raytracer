#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Point.hpp"
#include "Vector.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "PGMOut.hpp"

#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

class Raytracer {
public:
	Raytracer() {};

	std::vector<std::vector<int>> to_raster(int resolution) {
		std::cout << "P2\n"; // Magic PBM bytes
    	std::cout << resolution << ' ' << resolution << '\n';
   	 	std::cout << "255\n"; // This means that 1 should be displayed as white.

   	 	double viewport_scale_factor{resolution == 1 ? 1 : 2. / resolution};
    	double viewport_shift{1 - 1. / resolution};

    	struct Point pointCamera;
	    pointCamera.coord[0] = 0;
	    pointCamera.coord[1] = 0;
	    pointCamera.coord[2] = 5;

	    struct Point pointSphere;
	    pointSphere.coord[0] = 0;
	    pointSphere.coord[1] = 0;
	    pointSphere.coord[2] = -5;
	    //double sphere[3]{0, 0, -5};
	    int radius = 1;

	    Sphere sphere(pointSphere, radius);

	    struct Vector vectorDelta;

	    // sphere.intersections(ray);
	    vectorDelta.coord[0] = pointCamera.coord[0] - pointSphere.coord[0];
	    vectorDelta.coord[1] = pointCamera.coord[1] - pointSphere.coord[1];
	    vectorDelta.coord[2] = pointCamera.coord[2] - pointSphere.coord[2];

	    std::vector<std::vector<int>> pic(resolution);

	    for (int y_pixel = 0; y_pixel < resolution; ++y_pixel) {
	        // To get the ray, we need the viewport coordinates. This is the y coordinate...
	        double viewport_y_coordinate{y_pixel * viewport_scale_factor - viewport_shift};
	        pic[y_pixel] = std::vector<int>(resolution);
	        // Ray ray;

	        for (int x_pixel = 0; x_pixel < resolution; ++x_pixel) {
	            // ... and the x coordinate.
	            double viewport_x_coordinate{x_pixel * viewport_scale_factor - viewport_shift};

	            // Now we get the vector from the camera to the viewport.
	            struct Vector vectorRayDirection;

	            vectorRayDirection.coord[0] = viewport_x_coordinate - pointCamera.coord[0];
	            vectorRayDirection.coord[1] = viewport_y_coordinate - pointCamera.coord[1];
	            vectorRayDirection.coord[2] = -pointCamera.coord[2];

	            // double vectorRayDirection.coord[3]{viewport_x_coordinate - pointCamera.coord[0],
	            //                         viewport_y_coordinate - pointCamera.coord[1],
	            //                         -pointCamera.coord[2]};

	            // And we want to make sure to normalize the ray we want to trace to a length of 1, because this will
	            // simplify many computations.

	            vectorRayDirection.normalize();


	            // double ray_length = sqrt(vectorRayDirection.coord[0] * vectorRayDirection.coord[0] +
	            //                          vectorRayDirection.coord[1] * vectorRayDirection.coord[1] +
	            //                          vectorRayDirection.coord[2] * vectorRayDirection.coord[2]);

	            // vectorRayDirection.coord[0] /= ray_length;
	            // vectorRayDirection.coord[1] /= ray_length;
	            // vectorRayDirection.coord[2] /= ray_length;

	            Ray ray(pointCamera, vectorRayDirection);

	            
	            std::vector<double> distances = sphere.intersections(ray);


	            
	            // for (unsigned i = 0; i < distances.size(); i++) {
	            // 	std::cout << distances[i] ; // << std::endl;
	            // }
	            // Now we can use the formula from the link to calculate b and c. Note that we can omit a, because
	            // ray.dot(ray)=1. This is, because we normalized it.

	            double b{(vectorDelta.coord[0] * ray.vectorDirection.coord[0] +
	                      vectorDelta.coord[1] * ray.vectorDirection.coord[1] +
	                      vectorDelta.coord[2] * ray.vectorDirection.coord[2]) *
	                     2};

	            //double b = vectorDelta.calcB(vectorRayDirection);

	            double c{ (vectorDelta.coord[0] * vectorDelta.coord[0] +
	                      vectorDelta.coord[1] * vectorDelta.coord[1] +
	                      vectorDelta.coord[2] * vectorDelta.coord[2]) -
	                     sphere.radius * sphere.radius };

	           	// double c = vectorDelta.calcC(radius);

	            // If there is an intersection, the discriminant >= 0, so we emit 1, to indicate full brightness, otherwise
	            // 0 to indicate black.
	            

	            double discriminant{b * b - 4 * c};
	            if (discriminant >= 0) {
	                //cout << "1 ";
	            	// std::cout << "=================HERE================\n";
		            // for (int i = 0; i < distances.size(); i++) {
		            // 	std::cout << distances[i] << std::endl;
		            // }
		            double brightness;
		            if (distances[0] <= distances[1]) {
		            	brightness = 10 - distances[0];
		            }
		            else {
		            	brightness = 10 - distances[1];
		            }

		            if (brightness < 0) brightness = 0;
	            	
		            int pixel_brightness = static_cast<int>(brightness * 255);
	                pic[y_pixel][x_pixel] = pixel_brightness;

	            } else {
	                //cout << "0 ";
	                pic[y_pixel][x_pixel] = 0;
	            }
	        }

	        // cout << '\n';
	    }
	    return pic;
	}
};


#endif