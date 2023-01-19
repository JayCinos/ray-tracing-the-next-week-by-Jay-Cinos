#pragma once
#ifndef COLOR
#define COLOR

#include "vec3.h"
#include <iostream>
#include <fstream>

using namespace std;

void write_color(ofstream& out, color pixel_color) {
	// Write the translated [0,255] value of each color component.
	out << static_cast<int>(255.999 * pixel_color.x()) << ' '
		<< static_cast<int>(255.999 * pixel_color.y()) << ' '
		<< static_cast<int>(255.999 * pixel_color.z()) << '\n';

}


#endif // !COLOR
