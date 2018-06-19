#include <iostream>
#include "vec3.h"

int main() {
    int nc = 200;
    int nr = 100;
    std::cout << "P3\n" << nc << " " << nr << "\n255" << std::endl;

    for (int j = 0; j < nr; j++) {
        for (int i = 0; i < nc; i++) {
            // Printing out P3-info linewise
            // Making r,g,b to be gradients of its full color
            vec3 col(float(i)/ float(nc), float(j)/float(nr), 0.2);
            float r = (col[0]) * 255.99;
            float g = (col[1]) * 255.99;
            float b = (col[2]) * 255.99;
            std::cout << int(r) << " " << int(g) << " " << int(b) << std::endl;
        }
    }
}

/*
 * This will produce:
P3
200 100
255
0 0 51
.
.
.
255 255 0


 * */
