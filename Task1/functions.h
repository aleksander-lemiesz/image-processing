//
// Created by creep on 13.10.2019.
//

#ifndef IMPROC1_FUNCTIONS_H
#define IMPROC1_FUNCTIONS_H

#endif //IMPROC1_FUNCTIONS_H

#include <iostream>
#include "CImg.h"
using namespace cimg_library;

// Working functions
int arg_check(int argc,char* argv);
void brightness_inc(CImg<unsigned char> img, int c, CImg<unsigned char> &result);
void brightness_dec(CImg<unsigned char> img, int c, CImg<unsigned char> &result);
void contrast(CImg<unsigned char> img, float step, int c, CImg<unsigned char> &result);
void negative(CImg<unsigned char> img, int c, CImg<unsigned char> &result);
void help();
void hflip(CImg<unsigned char> img, int c, CImg<unsigned char> &result);
void vflip(CImg<unsigned char> img, int c, CImg<unsigned char> &result);
void dflip(CImg<unsigned char> img, int c, CImg<unsigned char> &result);
void resize(CImg<unsigned char> img, float delta, int c, CImg<unsigned char> &result);
void alphaf(CImg<unsigned char> img, CImg<unsigned char> &result, int alpha, int channel);
void alphaimp(unsigned char **img, CImg<unsigned char> &result, int h, int w, int alpha, int channel);
void gmean(CImg<unsigned char> img, CImg<unsigned char> &result, int channel);
void gmeanimp(unsigned char **img, CImg<unsigned char> &result, int h, int w, int channel);
double mse(CImg<unsigned char> img, CImg<unsigned char> denoise, int c);
double pmse(CImg<unsigned char> original, CImg<unsigned char> denoise, int c);
double snr(CImg<unsigned char> original, CImg<unsigned char> denoise, int c);
double psnr(CImg<unsigned char> original, CImg<unsigned char> denoise, int c);
int md(CImg<unsigned char> original, CImg<unsigned char> denoise, int c);



