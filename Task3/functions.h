#ifndef IMPROC3_FUNCTIONS_H
#define IMPROC3_FUNCTIONS_H

#endif //IMPROC3_FUNCTIONS_H

#include "CImg.h"
using namespace cimg_library;
//typedef bool pixel;
typedef unsigned char pixel;

void create_image(CImg<pixel> &result, int c);

void dilation(CImg<pixel> const &image, CImg<pixel> &result, int c, std::array<bool, 9> window);

void erosion(CImg<pixel> const &image, CImg<pixel> &result, int c, std::array<bool, 9> window);

void opening(CImg<pixel> const &image, CImg<pixel> &result, int c, std::array<bool, 9> window);

void closing(CImg<pixel> const &image, CImg<pixel> &result, int c, std::array<bool, 9> window);

void HMT_transformation(CImg<pixel> const &image, CImg<pixel> &result, int c);
void mask_flip(std::array<bool, 9> array);

void equal_two_images(CImg<pixel> const &image, CImg<pixel> &result, int c);
bool is_not_empty(CImg<pixel> const &img);
void skeleton(CImg<pixel> const &image, CImg<pixel> &result, int c, std::array<bool, 9> window);

void growing(CImg<pixel> &image, CImg<pixel> &result, int userX, int userY, int condition);
void recursiveGrowing (CImg<pixel> &image, CImg<pixel> &result, int x, int y, int max, int min);