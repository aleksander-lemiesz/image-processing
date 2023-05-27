#include <iostream>
#include "CImg.h"
#include "functions.h"
#include <array>
#include <chrono>
using namespace cimg_library;
using namespace std;
typedef unsigned char pixel;

auto start = chrono::high_resolution_clock::now();
int main(int argc, char* argv[]) {

    const std::array<const std::string, 10> command = { "--DFT", "--IDFT", "--FFT",
                                                        "--IFFT", "--Low-pass", "--High-pass",
                                                        "--Band-pass", "--Band-cut",
                                                        "--High-pass-det", "--Phase-mod"};

    // For DFT and FFT and inverses
    char *img_name;
    char *phase;
    char *magnitude;

    img_name = argv[argc - 3];
    magnitude = argv[argc - 2];
    phase = argv[argc - 1];

    CImg<pixel> original;
    CImg<pixel> magnitudeResultImage;
    CImg<pixel> phaseResultImage;
    int channel;

    // For IDFT and IFFT
    char* orig_name;
    char* resulting_name;

    orig_name = argv[2];
    resulting_name = argv[3];

    CImg<pixel> orig_img;
    CImg<pixel> inverseResult;
    /*char *magnitudeImage;
    char *phaseImage;
    char *resultImage;

    magnitudeImage = argv[argc - 3];
    phaseImage = argv[argc - 2];
    resultImage = argv[argc - 1];

    CImg<pixel> magnitudeIMG;
    CImg<pixel> phaseIMG;
    CImg<pixel> inverseResult;*/

    //  For filters
    char* originalName;
    char* resultName;

    originalName = argv[argc - 2];
    resultName = argv[argc - 1];

    CImg<pixel> originalImage;
    CImg<pixel> result;


    if (argv[1] == command.at(0)) { // --DFT
        cout << "Executing DFT" << endl;
        CImg<pixel> image(img_name);
        original = image;
        channel = original.spectrum();

        magnitudeResultImage.assign(original._width, original._height, 1, channel);
        magnitudeResultImage = static_cast<pixel>(0);

        phaseResultImage.assign(original._width, original._height, 1, channel);
        phaseResultImage = static_cast<pixel>(0);

        cout << "Calling function " << endl;
        for (int i = 0; i < channel; ++i) {
            DFT(original, magnitudeResultImage, phaseResultImage, i);
        }
        cout << "Switching quarters" << endl;
        for (int i = 0; i < channel; ++i) {
            switchQuarters(magnitudeResultImage, i);
            switchQuarters(phaseResultImage, i);
        }
    } else if (argv[1] == command.at(1)) { // --IDFT
        cout << "Executing IDFT" << endl;

        CImg<pixel> image(orig_name);
        orig_img = image;
        channel = orig_img.spectrum();

        inverseResult.assign(orig_img._width, orig_img._height, 1, channel);
        inverseResult = static_cast<pixel>(0);

        for (int i = 0; i < channel; ++i) {
            filterWrapper(orig_img, inverseResult, "IDFT", 0, 0, i);
        }

        /*CImg<pixel> magImg(magnitudeImage);
        CImg<pixel> phasImg(phaseImage);
        magnitudeIMG = magImg;
        phaseIMG = phasImg;
        channel = magnitudeIMG.spectrum();

        inverseResult.assign(magnitudeIMG.width(), magnitudeIMG.height(), 1, magnitudeIMG.spectrum());
        inverseResult = static_cast<pixel>(0);

        cout << "Switching quarters" << endl;
        for (int i = 0; i < channel; ++i) {
            switchQuarters(magnitudeIMG, i);
            switchQuarters(phaseIMG, i);
        }
        cout << "Calling function" << endl;
        for (int i = 0; i < channel; ++i) {
            IDFT(magnitudeIMG, phaseIMG, inverseResult, i);
        }*/

    } else if (argv[1] == command.at(2)) { // --FFT
        cout << "Executing FFT" << endl;
        CImg<pixel> image(img_name);
        original = image;
        channel = original.spectrum();

        magnitudeResultImage.assign(original._width, original._height, 1, channel);
        magnitudeResultImage = static_cast<pixel>(0);

        phaseResultImage.assign(original._width, original._height, 1, channel);
        phaseResultImage = static_cast<pixel>(0);

        cout << "Calling function " << endl;
        for (int i = 0; i < channel; ++i) {
            FFT(original, magnitudeResultImage, phaseResultImage, i);
        }
        cout << "Switching quarters" << endl;
        for (int i = 0; i < channel; ++i) {
            switchQuarters(magnitudeResultImage, i);
            switchQuarters(phaseResultImage, i);
        }
    } else if (argv[1] == command.at(3)) { // --IFFT
        cout << "Executing IFFT" << endl;

        CImg<pixel> image(orig_name);
        orig_img = image;
        channel = orig_img.spectrum();

        inverseResult.assign(orig_img._width, orig_img._height, 1, channel);
        inverseResult = static_cast<pixel>(0);

        for (int i = 0; i < channel; ++i) {
            filterWrapper(orig_img, inverseResult, "IFFT", 0, 0, i);
        }

        /*CImg<pixel> magImg(magnitudeImage);
        CImg<pixel> phasImg(phaseImage);
        magnitudeIMG = magImg;
        phaseIMG = phasImg;
        channel = magnitudeIMG.spectrum();

        inverseResult.assign(magnitudeIMG.width(), magnitudeIMG.height(), 1, magnitudeIMG.spectrum());
        inverseResult = static_cast<pixel>(0);

        cout << "Switching quarters" << endl;
        for (int i = 0; i < channel; ++i) {
            switchQuarters(magnitudeIMG, i);
            switchQuarters(phaseIMG, i);
        }
        cout << "Calling function" << endl;
        for (int i = 0; i < channel; ++i) {
            IFFT(magnitudeIMG, phaseIMG, inverseResult, i);
        }*/
    } else if (argv[1] == command.at(4)) { // --Low-pass
        cout << "Executing Low-pass filter" << endl;
        string name = "Low_pass";
        int size = atoi(argv[2]);

        CImg<pixel> origImg(originalName);
        originalImage = origImg;
        channel = originalImage.spectrum();

        result.assign(originalImage.width(), originalImage.height(), 1, channel);
        result = static_cast<pixel>(0);

        cout << "Preparation finished" << endl;
        for (int i = 0; i < channel; ++i) {
            filterWrapper(originalImage, result, name, size, 0, i);
        }
    } else if (argv[1] == command.at(5)) { // --High-pass
        cout << "Executing High-pass filter" << endl;
        string name = "High_pass";
        int size = atoi(argv[2]);

        CImg<pixel> origImg(originalName);
        originalImage = origImg;
        channel = originalImage.spectrum();

        result.assign(originalImage.width(), originalImage.height(), 1, channel);
        result = static_cast<pixel>(0);

        cout << "Preparation finished" << endl;
        for (int i = 0; i < channel; ++i) {
            filterWrapper(originalImage, result, name, size, 0, i);
        }
    } else if (argv[1] == command.at(6)) { // --Band-pass
        cout << "Executing Band-pass filter" << endl;
        string name = "Band_pass";
        int size = atoi(argv[2]);
        int biggerSize = atoi(argv[3]);

        CImg<pixel> origImg(originalName);
        originalImage = origImg;
        channel = originalImage.spectrum();

        result.assign(originalImage.width(), originalImage.height(), 1, channel);
        result = static_cast<pixel>(0);

        cout << "Preparation finished" << endl;
        for (int i = 0; i < channel; ++i) {
            filterWrapper(originalImage, result, name, size, biggerSize, i);
        }
    } else if (argv[1] == command.at(7)) { // --Band-cut
        cout << "Executing Band-cut filter" << endl;
        string name = "Band_cut";
        int size = atoi(argv[2]);
        int biggerSize = atoi(argv[3]);

        CImg<pixel> origImg(originalName);
        originalImage = origImg;
        channel = originalImage.spectrum();

        result.assign(originalImage.width(), originalImage.height(), 1, channel);
        result = static_cast<pixel>(0);

        cout << "Preparation finished" << endl;
        for (int i = 0; i < channel; ++i) {
            filterWrapper(originalImage, result, name, size, biggerSize, i);
        }
    } else if (argv[1] == command.at(9)) { // --Phase-mod
        cout << "Executing phase modifying filter" << endl;
        string name = "Phase_mod";
        int size = atoi(argv[2]);
        int biggerSize = atoi(argv[3]);

        CImg<pixel> origImg(originalName);
        originalImage = origImg;
        channel = originalImage.spectrum();

        result.assign(originalImage.width(), originalImage.height(), 1, channel);
        result = static_cast<pixel>(0);

        cout << "Preparation finished" << endl;
        for (int i = 0; i < channel; ++i) {
            filterWrapper(originalImage, result, name, size, biggerSize, i);
        }
    } else if (argv[1] == command.at(8)) { // --High-pass-det
        cout << "Executing high pass detection filter" << endl;
        string name = "High_pass_det";
        int size = atoi(argv[2]);
        int biggerSize = atoi(argv[3]);

        CImg<pixel> origImg(originalName);
        originalImage = origImg;
        channel = originalImage.spectrum();

        result.assign(originalImage.width(), originalImage.height(), 1, channel);
        result = static_cast<pixel>(0);

        cout << "Preparation finished" << endl;
        for (int i = 0; i < channel; ++i) {
            filterWrapper(originalImage, result, name, size, biggerSize, i);
        }
    } else {
        cout << "No command like that" << endl;
        exit(0);
    }

    if (argv[1] == command.at(0) || argv[1] == command.at(2)) { // if DFT or FFT
        magnitudeResultImage.save_bmp(magnitude);
        phaseResultImage.save_bmp(phase);
    }
    if (argv[1] == command.at(1) || argv[1] == command.at(3)) { // if IDFT or IFFT
        inverseResult.save_bmp(resulting_name);
    }
    if (argv[1] == command.at(4) || argv[1] == command.at(5) ||
    argv[1] == command.at(6) || argv[1] == command.at(7) ||
    argv[1] == command.at(9) || argv[1] == command.at(8)){ // if Filter
        result.save_bmp(resultName);
    }

    auto finish = chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    cout << endl << "Elapsed time: " << elapsed.count() << " s" << endl;

    return 0;
}
