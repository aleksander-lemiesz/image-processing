#include <iostream>
#include <array>
#include <algorithm>
#include "CImg.h"
#include "functions.h"
using namespace cimg_library;

void histogram_color(CImg<unsigned char> const &image, CImg<unsigned char> &histogram, int c, unsigned int max) {
    const unsigned int h = image._height;
    const unsigned int w  = image._width;
    std::array<unsigned int, 256> histValues{};
    for (int i = 0; i < 256; ++i) {
        histValues.at(i) = 0;
    }

    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; ++y) {
            unsigned int pixel_value = image(x, y, 0, c);
            histValues.at(pixel_value)++;
        }
    }
    //  Putting information into histogram
    for (int x = 0; x < 256; ++x) {
        for (unsigned int y = 0; y < histValues.at(x); y++) {
            histogram(x, max + 5 - y, 0, c) = 255;
        }
    }
}
void histogram(CImg<unsigned char> const &image, CImg<unsigned char> &result_histogram, int channel) {
    //  Determining the max value of histogram
    std::array<unsigned int, 256> histValues{};
    unsigned int max = 0;
    for (int c = 0; c < channel; ++c) {
        for (int j = 0; j < 256; ++j) {
            histValues.at(j) = 0;
        }
        for (int x = 0; x < image._width; ++x) {
            for (int y = 0; y < image._height; ++y) {
                unsigned int pixel_value = image(x, y, 0, c);
                histValues.at(pixel_value)++;
            }
        }
        for (int i = 0; i < 256; ++i) {
            if (histValues.at(i) > max) {
                max = histValues.at(i);
            }
        }
    }

    unsigned int width = 20;
    CImg<unsigned char> histogram;
    histogram.assign(256, max+6, 1, channel);
    result_histogram.assign(256*width, max+6, 1, channel);
    for (int c = 0; c < channel; ++c) {
        histogram_color(image, histogram, c, max);
    }
    for (int c = 0; c < channel; ++c) {
        resize(histogram, width, c, result_histogram);
    }
}
void resize(CImg<unsigned char> img, float delta, int c, CImg<unsigned char> &result) {
    int width = img.width() * delta;
    int height = img.height();

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            int pixel = img(x/delta, y, 0,c);
            result(x, y , 0, c) = pixel;
        }
    }
}

void huniform(CImg<unsigned char> const &image, CImg<unsigned char> &result, int c) {

    const unsigned int h = image._height;
    const unsigned int w  = image._width;
    const auto N = (float)(h*w);

    //  Histogram calc
    std::array<unsigned int, 256> histValues{};
    for (int i = 0; i < 256; ++i) {
        histValues.at(i) = 0;
    }
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; ++y) {
            unsigned int pixel_value = image(x, y, 0, c);
            histValues.at(pixel_value)++;
        }
    }

    //  Actual function
    const float g_min = 0.0;
    const float g_max = 255.0;

    for (unsigned int x = 0; x < w; ++x) {
        for (unsigned int y = 0; y < h; ++y) {
            float histogram_sum = 0;
            unsigned int f = image(x, y, 0, c);
            for (unsigned int m = 0; m < f; ++m) {
                histogram_sum += histValues.at(m);
            }
            float result_value =  g_min - (g_max - g_min)*histogram_sum/N;
            int newresult_value = (int) round( -1 * round(result_value));
            if (newresult_value > 255) {
                newresult_value = 255;
            } else if (newresult_value < 0) {
                newresult_value = 0;
            }
            result(x, y, 0, c) = newresult_value;
        }
    }
}

double cmean(CImg<unsigned char> const &image, int c) {

    const unsigned int h = image._height;
    const unsigned int w  = image._width;
    const unsigned int N = h*w;

    //  Histogram calc
    std::array<unsigned int, 256> histValues{};
    for (int i = 0; i < 256; ++i) {
        histValues.at(i) = 0;
    }
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; ++y) {
            unsigned int pixel_value = image(x, y, 0, c);
            histValues.at(pixel_value)++;
        }
    }

    //  Calculating the mean
    double product_sum = 0;
    for (int m = 0; m < 256; ++m) {
        product_sum += m*histValues.at(m);
    }
    double mean = product_sum/N;
    return mean;
}

double cvariance(CImg<unsigned char> const &image, int c) {

    const unsigned int h = image._height;
    const unsigned int w  = image._width;
    const int channel = image.spectrum();
    const unsigned int N = h*w;

    //  Histogram calc
    std::array<unsigned int, 256> histValues{};
    for (int i = 0; i < 256; ++i) {
        histValues.at(i) = 0;
    }
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; ++y) {
            unsigned int pixel_value = image(x, y, 0, c);
            histValues.at(pixel_value)++;
        }
    }

    //  Calculating the mean
    double mean = 0;
    for (int color = 0; color < channel; ++color) {
        mean += cmean(image, color);
    }
    mean /= channel;

    // Calculating the Variance
    double product_sum = 0;
    for (int m = 0; m < 256; ++m) {
        double difference = m - mean;
        double square_difference = pow(difference, 2);
        product_sum += square_difference*histValues.at(m);
    }
    double variance = product_sum/N;
    return variance;
}

void optimized_slineid(CImg<unsigned char> const &image, CImg<unsigned char> &result, int channel) {

    const unsigned int h = image._height;
    const unsigned int w  = image._width;
    const unsigned int z = 0;

    auto **extension = new unsigned char*[h + 2];
    for (int i = 0; i < h + 2; ++i) {
        extension[i] = new unsigned char[w + 2];
    }
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            for (int c = 0; c < 3; ++c) {
                extension[y + 1][x + 1] =  image(x, y, z, channel);
                //  Filling the left and right column
                extension[y + 1][0] = image(0, y, z, channel);
                extension[y + 1][w + 1] = image(w - 1, y, z, channel);
            }
        }
    }
    memcpy(&extension[0][0], &extension[1][0], (w + 2) * sizeof(unsigned char));

    memcpy(&extension[h + 1][0], &extension[h][0], (w + 2) * sizeof(unsigned char));

    optimized_slineid_imp(extension, result, h+2, w+2, channel);

    //  Free memory of extension
    for (int i = 0; i < h + 2; ++i) {
        delete[] extension[i];
    }
    delete[] extension;
}
void optimized_slineid_imp(unsigned char **img, CImg<unsigned char> &result, int h, int w, int channel) {
    /*const std::array<const int, 9> window = {-1, 2, -1,
                                             -1, 2, -1,
                                             -1, 2, -1};*/
    //  Moving widow through the image
    for (int x = 1; x < (h - 1); ++x) {
        for (int y = 1; y < (w - 1); ++y) {

            //   Getting the value of image pixels into window
            /*int window_iterator = 0;
            int sum = window.at(0)*img[y-1][x-1] + window.at(1)*img[y-1][x] + window.at(2)*img[y-1][x+1]
                    + window.at(3)*img[y][x-1] + window.at(4)*img[y][x] + window.at(5)*img[y][x+1]
                    + window.at(6)*img[y+1][x-1] + window.at(7)*img[y+1][x] + window.at(8)*img[y+1][x+1];*/

            int sum = 2*(img[y-1][x] + img[y][x] + img[y+1][x]) - img[y-1][x-1] - img[y][x-1] - img[y+1][x-1]
                    - img[y-1][x+1] - img[y][x+1] - img[y+1][x+1];

            //std::cout << sum << " : ";// std::endl;
            sum += 50;
            if (sum > 255) {
                sum = 255;
            } else if (sum < 0) {
                sum = 0;
            }
            result(x-1, y-1, 0, channel) = sum;
        }
    }
}
void mask_flip(std::array<int, 9> mask) {
    for (int y = 0; y < (3/2); y++) {
        for (int x = 0; x < 3; x++) {
            int y2 = 3 - 1 - y;
            int old_val = mask.at(x + 3*y);
            mask.at(x + 3*y) = mask.at(x + 3*y2);
            mask.at(x + 3*y2) = old_val;
        }
    }
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < (3/2); x++) {
            int x2 = 3 - 1 - x;
            int old_val = mask.at(x + 3*y);
            mask.at(x + 3*y) = mask.at(x2 + 3*y);
            mask.at(x2 + 3*y) = old_val;
        }
    }
}
void slineid(CImg<unsigned char> const &image, CImg<unsigned char> &result, int channel, int mask_number) {

    const unsigned int h = image._height;
    const unsigned int w  = image._width;
    const unsigned int z = 0;

    auto **extension = new unsigned char*[h + 2];
    for (int i = 0; i < h + 2; ++i) {
        extension[i] = new unsigned char[w + 2];
    }
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            for (int c = 0; c < 3; ++c) {
                extension[y + 1][x + 1] =  image(x, y, z, channel);
                //  Filling the left and right column
                extension[y + 1][0] = image(0, y, z, channel);
                extension[y + 1][w + 1] = image(w - 1, y, z, channel);
            }
        }
    }
    memcpy(&extension[0][0], &extension[1][0], (w + 2) * sizeof(unsigned char));

    memcpy(&extension[h + 1][0], &extension[h][0], (w + 2) * sizeof(unsigned char));

    slineid_imp(extension, result, h+2, w+2, channel, mask_number);

    //  Free memory of extension
    for (int i = 0; i < h + 2; ++i) {
        delete[] extension[i];
    }
    delete[] extension;

}
void slineid_imp(unsigned char **img, CImg<unsigned char> &result, int h, int w, int channel, int mask_number) {
    const std::array<std::array<int,9>, 4> available_masks = {-1, 2, -1,
                                                                    -1, 2, -1,
                                                                              -1, 2, -1,

                                                                              -1, -1, 2,
                                                                              -1, 2, -1,
                                                                              2, -1, -1,

                                                                              -1, -1, -1,
                                                                              2, 2, 2,
                                                                              -1, -1, -1,

                                                                              2, -1, -1,
                                                                              -1, 2, -1,
                                                                              -1, -1, 2};

    std::array<int, 9> mask = available_masks.at(mask_number - 1);
    mask_flip(mask);

    //  Moving widow through the image
    for (int x = 1; x < (h - 1); ++x) {
        for (int y = 1; y < (w - 1); ++y) {

            int window_iterator = 0;
            int sum = 0;
            for (int yg = (y - 1); yg < (y + 2); ++yg) {
                for (int xg = (x - 1); xg < (x + 2); ++xg) {
                    sum += mask.at(window_iterator)*img[yg][xg];
                    window_iterator++;
                }
            }
            sum += 50;
            if (sum > 255) {
                sum = 255;
            } else if (sum < 0) {
                sum = 0;
            }
            result(x-1, y-1, 0, channel) = sum;
        }
    }
}

void orosenfeld(CImg<unsigned char> const &image, CImg<unsigned char> &result, int channel, const int P) {
    const unsigned int h = image._height; // M
    const unsigned int w  = image._width; // N
    const auto beginning = image.begin();
    const auto end = image.end();

    for (int n = 0; n < w; ++n) {
        for (int m = 0; m < h; ++m) {
            int sum = 0;

            for (int i = 1; i <= P; ++i) {
                if ( (&image(n + P - i, m, 0, channel) >= beginning) && (&image(n + P - i, m, 0, channel) <= end) )
                    sum += image(n + P - i, m, 0, channel);
            }
            for (int i = 1; i <= P; ++i) {
                if ( (&image(n - i, m, 0, channel) >= beginning) && (&image(n - i, m, 0, channel) <= end) )
                    sum -= image(n - i, m, 0, channel);
            }
            auto rosenfeld = (float) (sum / P);
            int rosenfeld_operator = round(rosenfeld);
            rosenfeld_operator += 20;
            if (rosenfeld_operator > 255) {
                rosenfeld_operator = 255;
            } else if (rosenfeld_operator < 0) {
                rosenfeld_operator = 0;
            }
            result(n, m, 0, channel) = rosenfeld_operator;
        }
    }
}