#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "Point.hpp"
#include "Vector.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "PGMOut.hpp"
#include "Raytracer.hpp"

#include <vector>

using namespace std;

// std::vector<double> intersections(Ray r) {
// 	std::vector<double> inters;
// 	inters.push_back(abs(this->centerPoint.coord[2]) + abs(r.startPoint.coord[2]));
// 	inters.push_back(abs(this->centerPoint.coord[1]) + abs(r.startPoint.coord[1]));
// 	inters.push_back(abs(this->centerPoint.coord[0]) - abs(r.startPoint.coord[0]));

// 	return inters;
// };

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return -1;
    }

    int resolution = atoi(argv[1]);

    // cout << "P2\n"; // Magic PBM bytes
    // cout << resolution << ' ' << resolution << '\n';
    // cout << "1\n"; // This means that 1 should be displayed as white.

    // // Our viewport is in the range [-1;1] in both x in y direction. To convert a pixel into a viewport
    // // coordinate, we need to scale it first by (coordinate * 2 / resolution). However, if the resolution
    // // is for example 2x2, we don't want rays at the four corners (-1;-1), (-1;1), (1;-1) and (1;1). If the
    // // viewport is divided by for pixels, is is a square subdivided by four squares. We want to cast a ray
    // // through the middle of each square:
    // //
    // //  (-1;1) x-+-x (1;1)
    // //         |o|o|
    // //         +-+-+
    // //         |o|o|
    // // (-1;-1) x-+-x (-1;1)
    // //
    // // In this 2x2 viewport, the 'x' are the corners, and the 'o' are the rays we want to trace. To center
    // // them, we need to add to them 1/resolution. In the case of resolution=2, this is 0.5.
    // //
    // // So to scale we do do the same thing for the and y value. For resolution=4, the desired rays are at
    // // the coordinates {-0.75, -0.25, 0.25, 0.75} in both x and y direction. The pixel coordinates are in
    // // the interval [0;3]. We multiply this with 2/resolution, which scales this value to interval [0;1.5].
    // // now we subtract 1 and add 1/resolution to scale it to the interval [-0.75;0.75]. This works for odd
    // // and even numbers, except 1, which needs special case handling.
    // double viewport_scale_factor{resolution == 1 ? 1 : 2. / resolution};
    // double viewport_shift{1 - 1. / resolution};

    // // The camera is located at (x=0;y=0;z=5).
    // struct Point pointCamera;
    // pointCamera.coord[0] = 0;
    // pointCamera.coord[1] = 0;
    // pointCamera.coord[2] = 5;

    // // double camera[3]{0, 0, 5};

    // // And there is a sphere at (0;0;-5) with radius 1.

    // struct Point pointSphere;
    // pointSphere.coord[0] = 0;
    // pointSphere.coord[1] = 0;
    // pointSphere.coord[2] = -5;
    // //double sphere[3]{0, 0, -5};
    // int radius = 1;

    // Sphere sphere(pointSphere, radius);

    // // Ray ray(pointCamera, );


    // // To compute intersections, consider this article:
    // // http://viclw17.github.io/2018/07/16/raytracing-ray-sphere-intersection/
    // // delta_{x,y,z} is the vector A-C

    // struct Vector vectorDelta;

    // // sphere.intersections(ray);
    // vectorDelta.coord[0] = pointCamera.coord[0] - pointSphere.coord[0];
    // vectorDelta.coord[1] = pointCamera.coord[1] - pointSphere.coord[1];
    // vectorDelta.coord[2] = pointCamera.coord[2] - pointSphere.coord[2];

    // // vectorDelta.vectorBetweenTwoPoints(pointCamera, pointSphere);

    // // double delta[3]{pointCamera.coord[0] - pointSphere.coord[0],
    // //                 pointCamera.coord[1] - pointSphere.coord[1],
    // //                 pointCamera.coord[2] - pointSphere.coord[2]};
    // // std::vector<double> delta = sphere.intersections(ray);

    // std::vector<std::vector<int>> pic(resolution);

    // for (int y_pixel = 0; y_pixel < resolution; ++y_pixel) {
    //     // To get the ray, we need the viewport coordinates. This is the y coordinate...
    //     double viewport_y_coordinate{y_pixel * viewport_scale_factor - viewport_shift};
    //     pic[y_pixel] = std::vector<int>(resolution);
    //     // Ray ray;

    //     for (int x_pixel = 0; x_pixel < resolution; ++x_pixel) {
    //         // ... and the x coordinate.
    //         double viewport_x_coordinate{x_pixel * viewport_scale_factor - viewport_shift};

    //         // Now we get the vector from the camera to the viewport.
    //         struct Vector vectorRayDirection;

    //         vectorRayDirection.coord[0] = viewport_x_coordinate - pointCamera.coord[0];
    //         vectorRayDirection.coord[1] = viewport_y_coordinate - pointCamera.coord[1];
    //         vectorRayDirection.coord[2] = -pointCamera.coord[2];

    //         // double vectorRayDirection.coord[3]{viewport_x_coordinate - pointCamera.coord[0],
    //         //                         viewport_y_coordinate - pointCamera.coord[1],
    //         //                         -pointCamera.coord[2]};

    //         // And we want to make sure to normalize the ray we want to trace to a length of 1, because this will
    //         // simplify many computations.

    //         vectorRayDirection.normalize();


    //         // double ray_length = sqrt(vectorRayDirection.coord[0] * vectorRayDirection.coord[0] +
    //         //                          vectorRayDirection.coord[1] * vectorRayDirection.coord[1] +
    //         //                          vectorRayDirection.coord[2] * vectorRayDirection.coord[2]);

    //         // vectorRayDirection.coord[0] /= ray_length;
    //         // vectorRayDirection.coord[1] /= ray_length;
    //         // vectorRayDirection.coord[2] /= ray_length;

    //         Ray ray(pointCamera, vectorRayDirection);

            
    //         std::vector<double> distances = sphere.intersections(ray);
    //         // for (unsigned i = 0; i < distances.size(); i++) {
    //         // 	std::cout << distances[i] ; // << std::endl;
    //         // }
    //         // Now we can use the formula from the link to calculate b and c. Note that we can omit a, because
    //         // ray.dot(ray)=1. This is, because we normalized it.

    //         double b{(vectorDelta.coord[0] * ray.vectorDirection.coord[0] +
    //                   vectorDelta.coord[1] * ray.vectorDirection.coord[1] +
    //                   vectorDelta.coord[2] * ray.vectorDirection.coord[2]) *
    //                  2};

    //         //double b = vectorDelta.calcB(vectorRayDirection);

    //         double c{ (vectorDelta.coord[0] * vectorDelta.coord[0] +
    //                   vectorDelta.coord[1] * vectorDelta.coord[1] +
    //                   vectorDelta.coord[2] * vectorDelta.coord[2]) -
    //                  sphere.radius * sphere.radius };

    //        	// double c = vectorDelta.calcC(radius);

    //         // If there is an intersection, the discriminant >= 0, so we emit 1, to indicate full brightness, otherwise
    //         // 0 to indicate black.

            
            

    //         double discriminant{b * b - 4 * c};
    //         if (discriminant >= 0) {
    //             //cout << "1 ";
    //             pic[y_pixel][x_pixel] = 1;
    //         } else {
    //             //cout << "0 ";
    //             pic[y_pixel][x_pixel] = 0;
    //         }
    //     }

    //     // cout << '\n';
    // }
    Raytracer tracer;
    PGMOut out;
    out.save(tracer.to_raster(resolution));



    return 0;
}