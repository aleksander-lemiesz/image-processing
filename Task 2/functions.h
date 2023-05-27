#ifndef IMPROC2_FUNCTIONS_H
#define IMPROC2_FUNCTIONS_H

#endif //IMPROC2_FUNCTIONS_H

#include <iostream>
#include <array>
#include "CImg.h"
using namespace cimg_library;

void histogram_color(CImg<unsigned char> const &image, CImg<unsigned char> &histogram, int c, unsigned int max);
void histogram(CImg<unsigned char> const &image, CImg<unsigned char> &histogram, int channel);
void resize(CImg<unsigned char> img, float delta, int c, CImg<unsigned char> &result);

void huniform(CImg<unsigned char> const &image, CImg<unsigned char> &result, int c);

double cmean(CImg<unsigned char> const &image, int c);

double cvariance(CImg<unsigned char> const &image, int c);

void optimized_slineid(CImg<unsigned char> const &image, CImg<unsigned char> &histogram, int channel);
void optimized_slineid_imp(unsigned char **img, CImg<unsigned char> &result, int h, int w, int channel);
void mask_flip(std::array<int, 9> mask);
void slineid(CImg<unsigned char> const &image, CImg<unsigned char> &result, int channel, int mask_number);
void slineid_imp(unsigned char **img, CImg<unsigned char> &result, int h, int w, int channel, int mask_number);

void orosenfeld(CImg<unsigned char> const &image, CImg<unsigned char> &result, int channel, const int P);