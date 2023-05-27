#ifndef IMPROC4_FUNCTIONS_H
#define IMPROC4_FUNCTIONS_H

#include "CImg.h"
#include <complex>
#include <vector>
#include <array>
#include <valarray>
using namespace cimg_library;
using namespace std;
typedef unsigned char pixel;

void switchQuarters(CImg<pixel> &result, int c);
void switchQuarters(CImg<double> &result, int c);
void switchQuarters(CImg<complex<double>> &result, int c);
double degreesToRadians(double degree);
double radiansToDegrees(double radian);

array<complex<double>, 512> DFT1D(array<complex<double>, 512> input);
void DFT(CImg<pixel> const &image, CImg<pixel> &magnitudeResult, CImg<pixel> &phaseResult, int c);

array<complex<double>, 512> IDFT1D(array<complex<double>, 512> input);
void IDFT(CImg<pixel> const &magnitudeImage, CImg<pixel> const &phaseImage, CImg<pixel> &result, int c);

unsigned long bitInverse(int originalIndex);
array<complex<double>, 512> FFT1D(array<complex<double>, 512> input);
void FFT1D_implementation(valarray<complex<double>>& input);
void FFT(CImg<pixel> const &image, CImg<pixel> &magnitudeResult, CImg<pixel> &phaseResult, int c);

array<complex<double>, 512> IFFT1D(array<complex<double>, 512> input);
void IFFT1D_implementation(valarray<complex<double>>& input);
void IFFT(CImg<pixel> const &magnitudeImage, CImg<pixel> const &phaseImage, CImg<pixel> &result, int c);

//  Filters
void filterWrapper(CImg<pixel> const &image, CImg<pixel> &result, string const &filterName, int size, int biggerSize, int c);

void LowPassFilter(CImg<double> const &magnitudeImage, CImg<double> &result, int radius, int c);
void HighPassFilter(CImg<double> const &magnitudeImage, CImg<double> &result, int radius, int c);
void BandPassFilter(CImg<double> const &magnitudeImage, CImg<double> &result, int radius, int radius2, int c);
void BandCutFilter(CImg<double> const &magnitudeImage, CImg<double> &result, int radius, int radius2, int c);
void HighPassDetectionFilter(CImg<double> const &magnitudeImage, CImg<double> &result, int radius, int userAngle, int c);
void PhaseModifyingFilter(CImg<complex<double>> const &image, CImg<complex<double>> &result, int l, int k, int c);

#endif //IMPROC4_FUNCTIONS_H
