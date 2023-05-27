#include <iostream>
#include <array>
#include "CImg.h"
#include "functions.h"
using namespace cimg_library;

int main(int argc, char* argv[]) {
                                           //           0                      1                    2
    std::array<std::string, 6> command = { "--histogram", "--huniform", "--cmean",
                                           //           3                      4                    5
                                           "--cvariance", "--slineid", "--orosenfeld"};

    char *img_name;
    char *result_name;

    if (argv[1] == command.at(2) || argv[1] == command.at(3)) {
        img_name = argv[argc - 1];
    } else {
        img_name = argv[argc - 2];
        result_name = argv[argc - 1];
    }
    CImg<unsigned char> image(img_name);
    int channel = image.spectrum();
    CImg<unsigned char> result;


    if (argv[1] == command.at(0)) { // --histogram
        histogram(image, result, channel);

    } else if (argv[1] == command.at(1)) { // --huniform
        result.assign(image._width, image._height, 1, channel);
        for (int c = 0; c < channel; ++c) {
            huniform(image, result, c);
        }

    } else if (argv[1] == command.at(2)) { // --cmean
        double channel_mean = 0;
        for (int c = 0; c < channel; ++c) {
            channel_mean += cmean(image, c);
        }
        channel_mean /= channel;
        std::cout << "The mean of image is " << channel_mean << std::endl;
        return 0;

    } else if (argv[1] == command.at(3)) { // --cvariance
        double channel_variance = 0;
        for (int c = 0; c < channel; ++c) {
            channel_variance += cvariance(image, c);
        }
        channel_variance /= channel;
        std::cout << "The variance of image is " << channel_variance << std::endl;
        return 0;

    } else if (argv[1] == command.at(4)) { // --slineid
        result.assign(image._width, image._height, 1, channel);
        if ( !atoi(argv[2]) ) {
            for (int c = 0; c < channel; ++c) {
                optimized_slineid(image, result, c);
            }
        } else {
            int mask_number = atoi(argv[2]);
            for (int c = 0; c < channel; ++c) {
                slineid(image, result, c, mask_number);
            }
        }

    } else if (argv[1] == command.at(5)) { // --orosenfeld
        result.assign(image._width, image._height, 1, channel);
        const int P = atoi(argv[2]);
        for (int c = 0; c < channel; ++c) {
            orosenfeld(image, result, c, P);
        }

    } else {
        std::cout << "There is no command like that." << std::endl;
    }
    result.save_bmp(result_name);

    return 0;
}