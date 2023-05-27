/*
                        Project done by Patrycja Klejszmit and Aleksander Lemiesz
                                        for Image Processing
 */
#include <iostream>
#include "CImg.h"
#include "functions.h"
#include <string>
using namespace cimg_library;

int main(int argc, char *argv[])
{
        // Checking if the command passed by user is correct:
    int check = arg_check(argc, argv[1]);
    if (check == 2)
    {
        return 0;
    }
    else if (check == 1)
    {
        return 1;
    }

        // Opening the image specified by user:
    char* img_name = argv[(argc-2)];
    CImg<unsigned char> image(img_name);
    int channel = image.spectrum();
    CImg<unsigned char> result(image.width(), image.height(), 1, channel);
    bool changed = true;

        // Checking which command should be executed:
    if (strncmp(argv[1], "--brightness", 12) == 0)
    {
        char choose = *argv[2];
        if (choose == '+')
        {
            for (int c = 0; c < channel; ++c) {
                brightness_inc(image, c, result);
            }
        }
        else if (choose == '-')
        {
            for (int c = 0; c < channel; ++c) {
                brightness_dec(image, c, result);
            }
        }
    }
    else if (strncmp(argv[1], "--contrast", 10) == 0)
    {
        std::string char_choose = argv[2];
        float float_choose = stof(char_choose);
        for (int c = 0; c < channel; ++c) {
            contrast(image, float_choose, c, result);
        }
    }
    else if (strncmp(argv[1], "--negative", 10) == 0)
    {
        for (int c = 0; c < channel; ++c) {
            negative(image, c, result);
        }
    }
    else if (strncmp(argv[1], "--hflip", 7) == 0)
    {
        for (int c = 0; c < channel; ++c) {
            hflip(image, c, result);
        }
    }
    else if (strncmp(argv[1], "--vflip", 7) == 0)
    {
        for (int c = 0; c < channel; ++c) {
            vflip(image, c, result);
        }
    }
    else if (strncmp(argv[1], "--dflip", 7) == 0)
    {
        for (int c = 0; c < channel; ++c) {
            dflip(image, c, result);
        }
    }
    else if (strncmp(argv[1], "--shrink", 8) == 0)
    {
        result.assign(image.width()/2, image.height()/2, 1, channel);
        for (int c = 0; c < channel; ++c) {
            resize(image, 0.5, c, result);
        }
    }
    else if (strncmp(argv[1], "--enlarge", 9) == 0)
    {
        result.assign(image.width()*2, image.height()*2, 1, channel);
        for (int c = 0; c < channel; ++c) {
            resize(image, 2, c, result);
        }
    }
    else if (strncmp(argv[1], "--alpha", 7) == 0)
    {
        std::string char_alpha = argv[2];
        int int_alpha = stoi(char_alpha);
        for (int c = 0; c < channel; ++c) {
            alphaf(image, result, int_alpha, c);
        }
    }
    else if (strncmp(argv[1], "--gmean", 7) == 0)
    {
        for (int c = 0; c < channel; ++c) {
            gmean(image, result, c);
        }
    }
    else if (strncmp(argv[1], "--mse", 5) == 0)
    {
        char* original_name = argv[(argc-1)];
        CImg<unsigned char> original(original_name);
        int orig_chan = original.spectrum();
        char* denoise_name = argv[(argc-2)];
        CImg<unsigned char> denoise(denoise_name);
        double mean_sqare_error = mse(original, denoise, orig_chan);
        std::cout << "Mean square error is: " << mean_sqare_error << std::endl;
        changed = false;
    }
    else if (strncmp(argv[1], "--pmse", 6) == 0)
    {
        char* original_name = argv[(argc-1)];
        CImg<unsigned char> original(original_name);
        int orig_chan = original.spectrum();
        char* denoise_name = argv[(argc-2)];
        CImg<unsigned char> denoise(denoise_name);
        double peak_mean_sqare_error = pmse(original, denoise, orig_chan);
        std::cout << "Peak mean square error is: " << peak_mean_sqare_error << std::endl;
        changed = false;
    }
    else if (strncmp(argv[1], "--snr", 5) == 0)
    {
        char* original_name = argv[(argc-1)];
        CImg<unsigned char> original(original_name);
        int orig_chan = original.spectrum();
        char* denoise_name = argv[(argc-2)];
        CImg<unsigned char> denoise(denoise_name);
        double sig_to_noise = snr(original, denoise, orig_chan);
        std::cout << "Signal to noise ratio is: " << sig_to_noise << std::endl;
        changed = false;
    }
    else if (strncmp(argv[1], "--psnr", 6) == 0)
    {
        char* original_name = argv[(argc-1)];
        CImg<unsigned char> original(original_name);
        int orig_chan = original.spectrum();
        char* denoise_name = argv[(argc-2)];
        CImg<unsigned char> denoise(denoise_name);
        double peak_sig_to_noise = psnr(original, denoise, orig_chan);
        std::cout << "Peak signal to noise ratio is: " << peak_sig_to_noise << std::endl;
        changed = false;
    }
    else if (strncmp(argv[1], "--md", 4) == 0)
    {
        char* original_name = argv[(argc-1)];
        CImg<unsigned char> original(original_name);
        int orig_chan = original.spectrum();
        char* denoise_name = argv[(argc-2)];
        CImg<unsigned char> denoise(denoise_name);
        int max_diff = 0;
        for (int c = 0; c < orig_chan; ++c) {
            max_diff += md(original, denoise, c);
        }
        max_diff /= 3;
        std::cout << "Maximum difference is: " << max_diff << std::endl;
        changed = false;
    }
    //  Ending program and saving result if necessary
    if (changed) {
        char* result_name = argv[argc - 1];
        result.save_bmp(result_name);
    }
    return 0;
}
