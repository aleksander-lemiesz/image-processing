#define _USE_MATH_DEFINES
#include "functions.h"
#include <cmath>
#include <complex>
#include <iostream>
#include <vector>
#include <bitset>
#include <valarray>

using namespace cimg_library;
using namespace std;
typedef unsigned char pixel;

//  Additional functions
void switchQuarters(CImg<pixel> &result, int c) {
    auto h = result.height();
    auto w = result.width();

    CImg<pixel> firstQuarter;
    firstQuarter.assign(w/2, h/2, 1, result.spectrum());

    CImg<pixel> secondQuarter;
    secondQuarter.assign(w/2, h/2, 1, result.spectrum());

    CImg<pixel> thirdQuarter;
    thirdQuarter.assign(w/2, h/2, 1, result.spectrum());

    CImg<pixel> fourthQuarter;
    fourthQuarter.assign(w/2, h/2, 1, result.spectrum());

    for (int y = 0; y < h/2; ++y) {
        for (int x = 0; x < w/2; ++x) {
            firstQuarter(x, y, 0, c) = result(x, y, 0, c);
        }
    }
    for (int y = 0; y < h/2; ++y) {
        for (int x = 0; x < w/2; ++x) {
            secondQuarter(x, y, 0, c) = result(x + w / 2, y, 0, c);
        }
    }
    for (int y = 0; y < h/2; ++y) {
        for (int x = 0; x < w/2; ++x) {
            thirdQuarter(x, y, 0, c) = result(x, y + h / 2, 0, c);
        }
    }
    for (int y = 0; y < h/2; ++y) {
        for (int x = 0; x < w/2; ++x) {
            fourthQuarter(x, y, 0, c) = result(x + w / 2, y + h / 2, 0, c);
        }
    }

    for (int y = 0; y < h/2; ++y) {
        for (int x = 0; x < w/2; ++x) {
            result(x, y, 0, c) = fourthQuarter(x, y, 0, c);
        }
    }
    for (int y = 0; y < h/2; ++y) {
        for (int x = 0; x < w/2; ++x) {
            result(x + w / 2, y, 0, c) = thirdQuarter(x, y, 0, c);
        }
    }
    for (int y = 0; y < h/2; ++y) {
        for (int x = 0; x < w/2; ++x) {
            result(x, y + h / 2, 0, c) = secondQuarter(x, y, 0, c);
        }
    }
    for (int y = 0; y < h/2; ++y) {
        for (int x = 0; x < w/2; ++x) {
            result(x + w / 2, y + h / 2, 0, c) = firstQuarter(x, y, 0, c);
        }
    }
}
void switchQuarters(CImg<double> &result, int c) {
    auto h = result.height();
    auto w = result.width();

    CImg<double> firstQuarter;
    firstQuarter.assign(w/2, h/2, 1, result.spectrum());

    CImg<double> secondQuarter;
    secondQuarter.assign(w/2, h/2, 1, result.spectrum());

    CImg<double> thirdQuarter;
    thirdQuarter.assign(w/2, h/2, 1, result.spectrum());

    CImg<double> fourthQuarter;
    fourthQuarter.assign(w/2, h/2, 1, result.spectrum());

    for (int y = 0; y < h/2; ++y) {
        for (int x = 0; x < w/2; ++x) {
            firstQuarter(x, y, 0, c) = result(x, y, 0, c);
        }
    }
    for (int y = 0; y < h/2; ++y) {
        for (int x = 0; x < w/2; ++x) {
            secondQuarter(x, y, 0, c) = result(x + w / 2, y, 0, c);
        }
    }
    for (int y = 0; y < h/2; ++y) {
        for (int x = 0; x < w/2; ++x) {
            thirdQuarter(x, y, 0, c) = result(x, y + h / 2, 0, c);
        }
    }
    for (int y = 0; y < h/2; ++y) {
        for (int x = 0; x < w/2; ++x) {
            fourthQuarter(x, y, 0, c) = result(x + w / 2, y + h / 2, 0, c);
        }
    }

    for (int y = 0; y < h/2; ++y) {
        for (int x = 0; x < w/2; ++x) {
            result(x, y, 0, c) = fourthQuarter(x, y, 0, c);
        }
    }
    for (int y = 0; y < h/2; ++y) {
        for (int x = 0; x < w/2; ++x) {
            result(x + w / 2, y, 0, c) = thirdQuarter(x, y, 0, c);
        }
    }
    for (int y = 0; y < h/2; ++y) {
        for (int x = 0; x < w/2; ++x) {
            result(x, y + h / 2, 0, c) = secondQuarter(x, y, 0, c);
        }
    }
    for (int y = 0; y < h/2; ++y) {
        for (int x = 0; x < w/2; ++x) {
            result(x + w / 2, y + h / 2, 0, c) = firstQuarter(x, y, 0, c);
        }
    }
}
void switchQuarters(CImg<complex<double>> &result, int c) {
    auto h = result.height();
    auto w = result.width();

    CImg<complex<double>> firstQuarter;
    firstQuarter.assign(w/2, h/2, 1, result.spectrum());

    CImg<complex<double>> secondQuarter;
    secondQuarter.assign(w/2, h/2, 1, result.spectrum());

    CImg<complex<double>> thirdQuarter;
    thirdQuarter.assign(w/2, h/2, 1, result.spectrum());

    CImg<complex<double>> fourthQuarter;
    fourthQuarter.assign(w/2, h/2, 1, result.spectrum());

    for (int y = 0; y < h/2; ++y) {
        for (int x = 0; x < w/2; ++x) {
            firstQuarter(x, y, 0, c) = result(x, y, 0, c);
        }
    }
    for (int y = 0; y < h/2; ++y) {
        for (int x = 0; x < w/2; ++x) {
            secondQuarter(x, y, 0, c) = result(x + w / 2, y, 0, c);
        }
    }
    for (int y = 0; y < h/2; ++y) {
        for (int x = 0; x < w/2; ++x) {
            thirdQuarter(x, y, 0, c) = result(x, y + h / 2, 0, c);
        }
    }
    for (int y = 0; y < h/2; ++y) {
        for (int x = 0; x < w/2; ++x) {
            fourthQuarter(x, y, 0, c) = result(x + w / 2, y + h / 2, 0, c);
        }
    }

    for (int y = 0; y < h/2; ++y) {
        for (int x = 0; x < w/2; ++x) {
            result(x, y, 0, c) = fourthQuarter(x, y, 0, c);
        }
    }
    for (int y = 0; y < h/2; ++y) {
        for (int x = 0; x < w/2; ++x) {
            result(x + w / 2, y, 0, c) = thirdQuarter(x, y, 0, c);
        }
    }
    for (int y = 0; y < h/2; ++y) {
        for (int x = 0; x < w/2; ++x) {
            result(x, y + h / 2, 0, c) = secondQuarter(x, y, 0, c);
        }
    }
    for (int y = 0; y < h/2; ++y) {
        for (int x = 0; x < w/2; ++x) {
            result(x + w / 2, y + h / 2, 0, c) = firstQuarter(x, y, 0, c);
        }
    }
}
unsigned long bitInverse(int originalIndex) { // Tested and working :D
    unsigned long newIndex = 0;
    bitset<sizeof(originalIndex)> bitIndex(originalIndex);
    for (int i = 0; i < sizeof(int)/2; ++i) {
        bool temp = bitIndex[i];
        bitIndex[i] = bitIndex[sizeof(int) - 1 - i];
        bitIndex[sizeof(int) - 1 - i] = temp;
    }
    newIndex = bitIndex.to_ulong();
    return newIndex;
}
double degreesToRadians(double degree){
    return degree * M_PI / 180.0;
}
double radiansToDegrees(double radian) {
    return radian * 180.0 / M_PI;
}

//  DFT
array<complex<double>, 512> DFT1D(array<complex<double>, 512> input) { // Tested and working great :D
    array<complex<double>, 512> output;
    auto N = output.size();
    for (int k = 0; k < N; ++k) { // output
        complex<double> sum(0.0, 0.0);

        for (int n = 0; n < N; ++n) { // input
            double angle = 2 * M_PI * n * k / N;
            complex<double> zn(cos(angle), -sin(angle));
            complex<double> result = input.at(n) * zn;
            sum += result;
        }
        output.at(k) = sum;
    }
    return output;
}
void DFT(CImg<pixel> const &image, CImg<pixel> &magnitudeResult, CImg<pixel> &phaseResult, int c) {

    CImg<complex<double>> result1(image._width, image._height, 1, image.spectrum());
    CImg<complex<double>> result2(image._width, image._height, 1, image.spectrum());

    //cout << "In function : ";
    const int h = image.height();
    const int w = image.width();
    int max = 0;

    // DFT for rows
    array<complex<double>, 512> rows;
    array<complex<double>, 512> rowsDFT;
    for (int y = 0; y < h; ++y) {
        for (int n = 0; n < 512; ++n) {
            // copying rows
            auto imageVal = static_cast<double>(image(n, y, 0, c));
            complex<double> imageComplex(imageVal, 0.0);
            rows.at(n) = imageComplex;
        }
        rowsDFT = DFT1D(rows);
        for (int n = 0; n < 512; ++n) {
            int tmp = abs(rowsDFT.at(n));
            if (max < tmp)
                max = tmp;
            result1(n, y, 0, c) = rowsDFT.at(n);
        }
    }

    // DFT for columns
    array<complex<double>, 512> columns;
    array<complex<double>, 512> columnsDFT;
    for (int x = 0; x < w; ++x) {
        for (int n = 0; n < 512; ++n) {
            // copying columns
            /*auto imageVal = static_cast<double>(intermediateResultReal(x, n, 0, c));
            complex<double> imageComplex(imageVal, 0.0);
            columns.at(n) = imageComplex;*/
            complex<double> imageComplex = result1(x, n, 0, c);
            columns.at(n) = imageComplex;
        }
        columnsDFT = DFT1D(columns);
        for (int n = 0; n < 512; ++n) {
            //  Filling the second result
            int tmp = abs(columnsDFT.at(n));
            if (max < tmp)
                max = tmp;
            result2(x, n, 0, c) = columnsDFT.at(n);

            /*double C = 1.00;
            double magnitude = log( 1 + abs(columnsDFT.at(n))) * C;
            if (magnitude > 255)
                magnitude = 255;
            magnitudeResult(x, n, 0, c) = static_cast<pixel>(magnitude);
            //  Filling the phase result
            double phase = arg(columnsDFT.at(n));
            if (phase > 255)
                phase = 255;
            phaseResult(x, n, 0, c) = static_cast<pixel>(phase);*/
        }
    }
    double C = 255 / (log(1 + max));
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            //  Filling the magnitude result
            magnitudeResult(x, y, 0, c) = C * log(1 + abs(result2(x, y, 0, c)));
            //  Filling the phase result
            double phase = arg(result2(x, y, 0, c));
            double phaseShift = (phase + M_PI) * 40.5845;
            double rounded = round(phaseShift);
            phaseResult(x, y, 0, c) = static_cast<pixel>(rounded);
        }
    }
}

//  IDFT
array<complex<double>, 512> IDFT1D(array<complex<double>, 512> input) { // Tested and working :D
    array<complex<double>, 512> output;
    auto N = input.size();
    for (int n = 0; n < N; ++n) {
        complex<double> sum(0.0, 0.0);

        for (int k = 0; k < N; ++k) {
            double angle = 2 * M_PI * n * k / N;
            complex<double> zn(cos(angle), sin(angle));
            complex<double> result = input.at(k) * zn;
            sum += result;
        }
        complex<double> comN(N, 1.0);
        output.at(n) = sum / comN;
    }
    return output;
}
void IDFT(CImg<pixel> const &magnitudeImage, CImg<pixel> const &phaseImage, CImg<pixel> &result, int c) {

    /**
    //  For testing IDFT1D
    complex<double> x0(2.0,0.0);
    complex<double> x1(-2.0,-2.0);
    complex<double> x2(0.0,-2.0);
    complex<double> x3(4.0,4.0);

    array<complex<double>, 4> inverse {x0, x1, x2, x3};

    for (int i = 0; i < 4; ++i) {
        cout << inverse.at(i) << " : ";
    }
    cout << endl;

    array<complex<double>, 4> original = IDFT1D(inverse);

    for (int i = 0; i < 4; ++i) {
        cout << original.at(i) << " : ";
    }
    cout << endl;
    exit(0);*/

    const int h = magnitudeImage.height();
    const int w = magnitudeImage.width();
    const int C = magnitudeImage.spectrum();

    CImg<complex<double>> originalValues(w, h, 1, C);
    CImg<complex<double>> columnsResult(w, h, 1, C);
    CImg<complex<double>> rowsResult(w, h, 1, C);
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            double magnitude = magnitudeImage(x, y, 0, c);
            double phase = phaseImage(x, y, 0, c);
            originalValues(x, y, 0, c) = polar(magnitude, -phase);
        }
    }

    //  IDFT for columns
    array<complex<double>, 512> columns;
    array<complex<double>, 512> columnsIDFT;
    for (int x = 0; x < w; ++x) {
        for (int n = 0; n < 512; ++n) {
            // copying columns
            columns.at(n) = originalValues(x, n, 0, c);
        }
        columnsIDFT = IDFT1D(columns);
        for (int n = 0; n < 512; ++n) {
            //  Filling the first result
            columnsResult(x, n, 0, c) = columnsIDFT.at(n);
        }
    }
    // IDFT for rows
    array<complex<double>, 512> rows;
    array<complex<double>, 512> rowsIDFT;
    for (int y = 0; y < h; ++y) {
        for (int n = 0; n < 512; ++n) {
            // copying rows
            rows.at(n) = columnsResult(n, y, 0, c);
        }
        rowsIDFT = IDFT1D(rows);
        for (int n = 0; n < 512; ++n) {
            //  Filling the second result
            rowsResult(n, y, 0, c) = rowsIDFT.at(n);
        }
    }

    // Saving the result
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            result(x, y, 0, c) = real(rowsResult(x, y, 0, c));
        }
    }
}

//  FFT
array<complex<double>, 512> FFT1D(array<complex<double>, 512> input) {
    array<complex<double>, 512> output;
    auto N = input.size();

    valarray<complex<double>> copy(N);
    for (int i = 0; i < N; ++i) {
        copy[i] = input.at(i);
    }
    FFT1D_implementation(copy);
    for (int i = 0; i < N; ++i) {
        output.at(i) = copy[i];
    }
    return output;
}
void FFT1D_implementation(valarray<complex<double>>& input) { // Tested and working :D
    const auto N = input.size();

    //  If the size is one or less there is nothing to do
    if (N <= 1)
        return;

    // Division into even and odd indexes
    valarray<complex<double>> even_indexes = input[std::slice(0, N / 2, 2)];
    valarray<complex<double>> odd_indexes = input[std::slice(1, N / 2, 2)];

    // Recurring one level more
    FFT1D_implementation(even_indexes);
    FFT1D_implementation(odd_indexes);

    //  Calculating the value
    for (int k = 0; k < N/2; ++k) {
        //  The butterfly
        complex<double> z = polar(1.0, -2 * M_PI * k / N) * odd_indexes[k];
        input[k] = even_indexes[k] + z;
        input[k + N / 2] = even_indexes[k] - z;
    }
}
void FFT(CImg<pixel> const &image, CImg<pixel> &magnitudeResult, CImg<pixel> &phaseResult, int c) {
    /**int n = 2;
    int N = bitInverse(n);
    cout << N << endl;
    exit(0);*/

    CImg<complex<double>> result1(image._width, image._height, 1, image.spectrum());
    CImg<complex<double>> result2(image._width, image._height, 1, image.spectrum());

    //cout << "In function : ";
    const int h = image.height();
    const int w = image.width();
    int max = 0;

    // FFT for rows
    array<complex<double>, 512> rows;
    array<complex<double>, 512> rowsDFT;
    for (int y = 0; y < h; ++y) {
        for (int n = 0; n < 512; ++n) {
            // copying rows
            auto imageVal = static_cast<double>(image(n, y, 0, c));
            complex<double> imageComplex(imageVal, 0.0);
            rows.at(n) = imageComplex;
        }
        rowsDFT = FFT1D(rows);
        for (int n = 0; n < 512; ++n) {
            int tmp = abs(rowsDFT.at(n));
            if (max < tmp)
                max = tmp;
            result1(n, y, 0, c) = rowsDFT.at(n);
        }
    }

    // FFT for columns
    array<complex<double>, 512> columns;
    array<complex<double>, 512> columnsDFT;
    for (int x = 0; x < w; ++x) {
        for (int n = 0; n < 512; ++n) {
            // copying columns
            complex<double> imageComplex = result1(x, n, 0, c);
            columns.at(n) = imageComplex;
        }
        columnsDFT = FFT1D(columns);
        for (int n = 0; n < 512; ++n) {
            //  Filling the second result
            int tmp = abs(columnsDFT.at(n));
            if (max < tmp)
                max = tmp;
            result2(x, n, 0, c) = columnsDFT.at(n);
        }
    }
    double C = 255 / (log(1 + max));
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            //  Filling the magnitude result
            magnitudeResult(x, y, 0, c) = C * log(1 + abs(result2(x, y, 0, c)));
            //  Filling the phase result
            double phase = arg(result2(x, y, 0, c));
            double phaseShift = (phase + M_PI) * 40.5845;
            double rounded = round(phaseShift);
            phaseResult(x, y, 0, c) = static_cast<pixel>(rounded);
        }
    }
}

//  IFFT
array<complex<double>, 512> IFFT1D(array<complex<double>, 512> input) {
    array<complex<double>, 512> output;
    auto N = input.size();

    valarray<complex<double>> copy(N);
    for (int i = 0; i < N; ++i) {
        copy[i] = input.at(i);
    }
    IFFT1D_implementation(copy);
    for (int i = 0; i < N; ++i) {
        output.at(i) = copy[i];
    }
    return output;
}
void IFFT1D_implementation(valarray<complex<double>>& input) {
    const auto N = input.size();

    //  If the size is one or less there is nothing to do
    if (N <= 1)
        return;

    // Division into even and odd indexes
    valarray<complex<double>> even_indexes = input[std::slice(0, N / 2, 2)];
    valarray<complex<double>> odd_indexes = input[std::slice(1, N / 2, 2)];

    // Recurring one level more
    FFT1D_implementation(even_indexes);
    FFT1D_implementation(odd_indexes);

    //  Calculating the value
    const complex<double> complexN(N, 0.0);
    for (int k = 0; k < N/2; ++k) {
        //  The butterfly
        complex<double> z = polar(1.0, -2 * M_PI * k / N) * odd_indexes[k];
        input[k] = (even_indexes[k] + z) / complexN;
        input[k + N / 2] = (even_indexes[k] - z) / complexN;
    }
}
void IFFT(CImg<pixel> const &magnitudeImage, CImg<pixel> const &phaseImage, CImg<pixel> &result, int c) {
    /**
    //  For testing IFFT1D
    complex<double> x0(2.0,0.0);
    complex<double> x1(-2.0,-2.0);
    complex<double> x2(0.0,-2.0);
    complex<double> x3(4.0,4.0);

    array<complex<double>, 4> inverse {x0, x1, x2, x3};

    for (int i = 0; i < 4; ++i) {
        cout << inverse.at(i) << " : ";
    }
    cout << endl;

    array<complex<double>, 4> original = IFFT1D(inverse);

    for (int i = 0; i < 4; ++i) {
        cout << original.at(i) << " : ";
    }
    cout << endl;
    exit(0);
     */

    const int h = magnitudeImage.height();
    const int w = magnitudeImage.width();
    const int C = magnitudeImage.spectrum();

    CImg<complex<double>> originalValues(w, h, 1, C);
    CImg<complex<double>> columnsResult(w, h, 1, C);
    CImg<complex<double>> rowsResult(w, h, 1, C);
    //  Converting to imaginary numbers
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            double magnitude = magnitudeImage(x, y, 0, c);
            double phase = phaseImage(x, y, 0, c);
            double angle = phase / 40.5845 - M_PI;
            originalValues(x, y, 0, c) = polar(magnitude, -angle);
        }
    }

    //  IFFT for columns
    array<complex<double>, 512> columns;
    array<complex<double>, 512> columnsIDFT;
    for (int x = 0; x < w; ++x) {
        for (int n = 0; n < 512; ++n) {
            // copying columns
            columns.at(n) = originalValues(x, n, 0, c);
        }
        columnsIDFT = IFFT1D(columns);
        for (int n = 0; n < 512; ++n) {
            //  Filling the first result
            columnsResult(x, n, 0, c) = columnsIDFT.at(n);
        }
    }
    // IFFT for rows
    array<complex<double>, 512> rows;
    array<complex<double>, 512> rowsIDFT;
    for (int y = 0; y < h; ++y) {
        for (int n = 0; n < 512; ++n) {
            // copying rows
            rows.at(n) = columnsResult(n, y, 0, c);
        }
        rowsIDFT = IFFT1D(rows);
        for (int n = 0; n < 512; ++n) {
            //  Filling the second result
            rowsResult(n, y, 0, c) = rowsIDFT.at(n);
        }
    }

    // Saving the result
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            result(x, y, 0, c) = real(rowsResult(x, y, 0, c));
        }
    }
}

//  Filter
void filterWrapper(CImg<pixel> const &image, CImg<pixel> &result, string const &filterName, int size, int biggerSize, int c) {
    //  Performing FFT
    cout << "Performing DFT" << endl;
    const int h = image.height();
    const int w = image.width();
    const int C = image.spectrum();

    CImg<complex<double>> rowsFFTResult(w, h, 1, C);
    CImg<complex<double>> columnsFFTResult(w, h, 1, C);
    CImg<complex<double>> FFTResult(w, h, 1, C);
    CImg<double> magnitudeResult(w, h, 1, C);
    CImg<double> phaseResult(w, h, 1, C);

    // FFT for rows
    array<complex<double>, 512> rows;
    array<complex<double>, 512> rowsDFT;
    for (int y = 0; y < h; ++y) {
        for (int n = 0; n < 512; ++n) {
            // copying rows
            auto imageVal = static_cast<double>(image(n, y, 0, c));
            complex<double> imageComplex(imageVal, 0.0);
            rows.at(n) = imageComplex;
        }
        if (filterName == "IDFT") {
            rowsDFT = DFT1D(rows);
        } else {
            rowsDFT = FFT1D(rows);
        }
        for (int n = 0; n < 512; ++n) {
            rowsFFTResult(n, y, 0, c) = rowsDFT.at(n);
        }
    }

    // FFT for columns
    array<complex<double>, 512> columns;
    array<complex<double>, 512> columnsDFT;
    for (int x = 0; x < w; ++x) {
        for (int n = 0; n < 512; ++n) {
            // copying columns
            columns.at(n) = rowsFFTResult(x, n, 0, c);
        }
        if (filterName == "IDFT") {
            columnsDFT = DFT1D(columns);
        } else {
            columnsDFT = FFT1D(columns);
        }
        for (int n = 0; n < 512; ++n) {
            //  Filling the second result
            columnsFFTResult(x, n, 0, c) = columnsDFT.at(n);
        }
    }
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            //  Filling the magnitude result
            magnitudeResult(x, y, 0, c) = abs(columnsFFTResult(x, y, 0, c));
            //  Filling the phase result
            phaseResult(x, y, 0, c) = arg(columnsFFTResult(x, y, 0, c));
        }
    }

    //  Filtering
    switchQuarters(magnitudeResult, c);
    CImg<double> filtered(w, h, 1, C);
    filtered = magnitudeResult;

    if (filterName != "IDFT" && filterName != "IFFT") {
        cout << "Filtering" << endl;
    }
    if (filterName == "Low_pass") {
        LowPassFilter(magnitudeResult, filtered, size, c);
    } else if (filterName == "High_pass") {
        HighPassFilter(magnitudeResult, filtered, size, c);
    } else if (filterName == "Band_pass") {
        BandPassFilter(magnitudeResult, filtered, size, biggerSize, c);
    } else if (filterName == "Band_cut") {
        BandCutFilter(magnitudeResult, filtered, size, biggerSize, c);
    } else if (filterName == "High_pass_det") {
        HighPassDetectionFilter(magnitudeResult, filtered, size, biggerSize, c);
    } else if (filterName == "Phase_mod") {
        //filtered = phaseResult;
        CImg<complex<double>> phaseModResult(w, h, 1, C);
        switchQuarters(columnsFFTResult, c);
        PhaseModifyingFilter(columnsFFTResult, phaseModResult, size, biggerSize, c);
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                //  Filling the magnitude result
                filtered(x, y, 0, c) = abs(phaseModResult(x, y, 0, c));
                //  Filling the phase result
                phaseResult(x, y, 0, c) = arg(phaseModResult(x, y, 0, c));
            }
        }
        switchQuarters(phaseResult, c);
    }

    if (filterName != "IDFT" && filterName != "IFFT") {

        /**
        double C = 255 / (log(1 + max));
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                //  Filling the magnitude result
                magnitudeResult(x, y, 0, c) = C * log(1 + abs(result2(x, y, 0, c)));
                //  Filling the phase result
                double phase = arg(result2(x, y, 0, c));
                double phaseShift = (phase + M_PI) * 40.5845;
                double rounded = round(phaseShift);
                phaseResult(x, y, 0, c) = static_cast<pixel>(rounded);
            }
        }*/

        CImg<pixel> displayMag(w, h, 1, 1);
        CImg<pixel> displayPhase(w, h, 1, 1);


        double max = 0;
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                if (max < filtered(x, y, 0, c)) {
                    max = filtered(x, y, 0, c);
                }
            }
        }
        double X = 255.0 / (log(1 + max));

        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                displayMag(x, y) = X * log(1 + filtered(x, y, 0, c));
                displayPhase(x, y) = (phaseResult(x, y, 0, c) + M_PI) * 40.5845;
            }
        }
        switchQuarters(displayPhase, 0);

        CImgDisplay mag(displayMag);
        CImgDisplay phase(displayPhase);
        system("Pause");
    }
    switchQuarters(filtered, c);

    //  Performing IFFT
    cout << "Performing IDFT" << endl;

    CImg<complex<double>> originalValues(w, h, 1, C);
    CImg<complex<double>> columnsResult(w, h, 1, C);
    CImg<complex<double>> rowsResult(w, h, 1, C);
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            double magnitude = filtered(x, y, 0, c);
            double phase = phaseResult(x, y, 0, c);
            if (filterName == "IDFT") {
                originalValues(x, y, 0, c) = polar(magnitude, phase);
            } else {
                originalValues(x, y, 0, c) = polar(magnitude, -phase);
            }
        }
    }
    //  IFFT for columns
    array<complex<double>, 512> columnsIDFT;
    for (int x = 0; x < w; ++x) {
        for (int n = 0; n < 512; ++n) {
            // copying columns
            columns.at(n) = originalValues(x, n, 0, c);
        }
        if (filterName == "IDFT") {
            columnsIDFT = IDFT1D(columns);
        } else {
            columnsIDFT = IFFT1D(columns);
        }
        for (int n = 0; n < 512; ++n) {
            //  Filling the first result
            columnsResult(x, n, 0, c) = columnsIDFT.at(n);
        }
    }
    // IFFT for rows
    array<complex<double>, 512> rowsIDFT;
    for (int y = 0; y < h; ++y) {
        for (int n = 0; n < 512; ++n) {
            // copying rows
            rows.at(n) = columnsResult(n, y, 0, c);
        }
        if (filterName == "IDFT") {
            rowsIDFT = IDFT1D(rows);
        } else {
            rowsIDFT = IFFT1D(rows);
        }
        for (int n = 0; n < 512; ++n) {
            //  Filling the second result
            rowsResult(n, y, 0, c) = rowsIDFT.at(n);
        }
    }

    // Saving the result
    cout << "Writting the result" << endl;
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            result(x, y, 0, c) = real(rowsResult(x, y, 0, c));
        }
    }
}

void LowPassFilter(CImg<double> const &magnitudeImage, CImg<double> &result, int radius, int c) {
    cout << "Low-pass implementation" << endl;
    const int h = magnitudeImage.height();
    const int w = magnitudeImage.width();

    const double middleX = w/2.0;
    const double middleY = h/2.0;

    result = 0.0;
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            double distance = sqrt(pow(x - middleX, 2) + pow(y - middleY, 2));
            if (distance <= radius) {
                result(x, y, 0, c) = magnitudeImage(x, y, 0, c);
            }
        }
    }
}
void HighPassFilter(CImg<double> const &magnitudeImage, CImg<double> &result, int radius, int c) {
    cout << "High-pass implementation" << endl;
    const int h = magnitudeImage.height();
    const int w = magnitudeImage.width();

    const double middleX = w/2.0;
    const double middleY = h/2.0;

    result = 0.0;
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            double distance = sqrt(pow(x - middleX, 2) + pow(y - middleY, 2));
            if (distance > radius) {
                result(x, y, 0, c) = magnitudeImage(x, y, 0, c);
            }
        }
    }
}
void BandPassFilter(CImg<double> const &magnitudeImage, CImg<double> &result, int radius, int radius2, int c) {
    cout << "Band-pass implementation" << endl;
    const int h = magnitudeImage.height();
    const int w = magnitudeImage.width();

    const double middleX = w/2.0;
    const double middleY = h/2.0;

    int biggerRadius;
    int smallerRadius;
    if (radius > radius2) {
        biggerRadius = radius;
        smallerRadius = radius2;
    } else {
        biggerRadius = radius2;
        smallerRadius = radius;
    }

    result = 0.0;
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            double distance = sqrt(pow(x - middleX, 2) + pow(y - middleY, 2));
            if (smallerRadius > distance || distance > biggerRadius) {
                result(x, y, 0, c) = magnitudeImage(x, y, 0, c);
            }
        }
    }
}
void BandCutFilter(CImg<double> const &magnitudeImage, CImg<double> &result, int radius, int radius2, int c) {
    cout << "Band-cut implementation" << endl;
    const int h = magnitudeImage.height();
    const int w = magnitudeImage.width();

    const double middleX = w/2.0;
    const double middleY = h/2.0;

    int biggerRadius;
    int smallerRadius;
    if (radius > radius2) {
        biggerRadius = radius;
        smallerRadius = radius2;
    } else {
        biggerRadius = radius2;
        smallerRadius = radius;
    }

    result = 0.0;
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            double distance = sqrt(pow(x - middleX, 2) + pow(y - middleY, 2));
            if (smallerRadius <= distance && distance <= biggerRadius) {
                result(x, y, 0, c) = magnitudeImage(x, y, 0, c);
            }
        }
    }
}
void HighPassDetectionFilter(CImg<double> const &magnitudeImage, CImg<double> &result, int radius, int userAngle, int c) {
    cout << "High-pass with detection implementation" << endl;
    const int h = magnitudeImage.height();
    const int w = magnitudeImage.width();

    int angle = 30;
    //int mirrorAngle = 180 - angle;

    const double middleX = w/2.0;
    const double middleY = h/2.0;

    result = 0.0;
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            double distance = sqrt(pow(x - middleX, 2) + pow(y - middleY, 2));
            double pixelAngle = radiansToDegrees(atan2(h/2.0 - y, x - w/2.0));
            if (distance > radius &&
            ((userAngle - angle < pixelAngle && pixelAngle < userAngle + angle) ||
            (-180 + userAngle - angle < pixelAngle && pixelAngle < -180 + userAngle - angle))) {
                result(x, y, 0, c) = magnitudeImage(x, y, 0, c);
            }
        }
    }
}
void PhaseModifyingFilter(CImg<complex<double>> const &image, CImg<complex<double>> &result, int k, int l, int c) {
    cout << "Phase modifying implementation" << endl;
    const int M = image.height();
    const int N = image.width();
    for (int m = 0; m < M; ++m) {
        for (int n = 0; n < N; ++n) {
            double magnitude = 1;
            double angle = (-n * k * 2 * M_PI / N) + (-m * l * 2 * M_PI / M) + (k + l) * M_PI;
            complex<double> P = polar(magnitude, angle);
            result(n, m, 0, c) = image(n, m, 0, c) * P;
        }
    }
}