#include <iostream>
#include <array>
#include <chrono>
#include "CImg.h"
#include "functions.h"
using namespace cimg_library;
using namespace std;
//typedef bool pixel;
typedef unsigned char pixel;

auto start = chrono::high_resolution_clock::now();
int main(int argc, char* argv[]) {
    const std::array<bool, 9> window = {true, true, true,
                                        true, true, true,
                                        true, true, true};

    const std::array<const std::string, 8> command = { "--dilation", "--erosion", "--opening",
                                                       "--closing", "--HMT", "--skeleton",
                                                       "--growing", "--create"};

    char *img_name;
    char *result_name;

    img_name = argv[argc - 2];
    result_name = argv[argc - 1];

    CImg<pixel> image(img_name);
    int channel = image.spectrum();
    CImg<pixel> result;
    result.assign(image._width, image._height, 1, channel);
    for (int x = 0; x < result.width(); ++x) {
        for (int y = 0; y < result.height(); ++y) {
            for (int i = 0; i < channel; ++i) {
                result(x,y,0,i) = 0;
            }
        }
    }

    if (argv[1] == command.at(0)) { // --dilation
        for (int i = 0; i < channel; ++i) {
            dilation(image, result, i, window);
        }

    } else if (argv[1] == command.at(1)) { // --erosion
        for (int i = 0; i < channel; ++i) {
            erosion(image, result, i, window);
        }

    } else if (argv[1] == command.at(2)) { // --opening
        for (int i = 0; i < channel; ++i) {
            opening(image, result, i, window);
        }

    } else if (argv[1] == command.at(3)) { // --closing
        for (int i = 0; i < channel; ++i) {
            closing(image, result, i, window);
        }

    } else if (argv[1] == command.at(4)) { // --HMT
        for (int i = 0; i < channel; ++i) {
            HMT_transformation(image, result, i);
        }

    } else if (argv[1] == command.at(5)) { // --skeleton
        //for (int i = 0; i < channel; ++i) {
        int i = 1;
            skeleton(image, result, i, window);
        //}

    } else if (argv[1] == command.at(6)) { // --growing
        result = image;
        const int condition = 20;
        unsigned int userX = atoi(argv[2]);
        unsigned int userY = atoi(argv[3]);
        growing(image, result, userX, userY, condition);

    } else if (argv[1] == command.at(7)) {
        for (int i = 0; i < channel; ++i) {
            create_image(result, i);
        }

    } else {
        std::cout << "There is no command like that." << std::endl;
    }
    result.save_bmp(result_name);
    auto finish = chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    cout << endl << "Elapsed time: " << elapsed.count() << " s" << endl;

    return 0;
}