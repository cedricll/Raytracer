#ifndef PGMOut_H
#define PGMOut_H

#include <stdlib.h>
#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

class PGMOut {

public:
	PGMOut() {};

	void save(std::vector<std::vector<int>> arr2D) {
		this->pic = arr2D;
		for (unsigned i = 0; i < arr2D.size(); i++) {
			for (unsigned j = 0; j < arr2D[i].size(); j++) {
				if (arr2D[i][j] > 255) {
					std::cout << 255 << " ";
				} else {
					std::cout << arr2D[i][j] << " ";
				}
				
			}
			std::cout << '\n';
		}
	}

	std::vector<std::vector<int>> pic ;
};

#endif