//
// Created by creep on 13.10.2019.
//

#include <iostream>
#include "CImg.h"
#include "functions.h"
using namespace cimg_library;

void help()
{
    std::cout << "This command line program uses arguments to operate. The syntax is following:" << std::endl;
    std::cout << "The first argument has to be the operation you want to perform. ";
    std::cout << "The last argument should be the image name that will be the result of operation. ";
    std::cout << "Before the last argument there should be the name of file to change. ";
    std::cout << "The commands to compare the images do not create image so do not pass name for the new file. ";
    std::cout << "It will not be changed. New image will be created. " << std::endl;
    std::cout << "The list of commands: " << std::endl;
    std::cout << "--brightness , with + or - right after to specify if you want to increase or decrease brightness" << std::endl;
    std::cout << "--contrast , with a number that indicates the intensity of the contrast" << std::endl;
    std::cout << "--negative" << std::endl;
    std::cout << "--hflip" << std::endl;
    std::cout << "--vflip" << std::endl;
    std::cout << "--dflip" << std::endl;
    std::cout << "--shrink , by factor 2" << std::endl;
    std::cout << "--enlarge , by factor 2" << std::endl;
    std::cout << "--alpha , with number form 0 to 8 to specify the value of apha for alpha-trimmed filter" << std::endl;
    std::cout << "--gmean , for geometric mean filter" << std::endl;
    std::cout << "--mse , for mean square error" << std::endl;
    std::cout << "--pmse , for peak mean square error" << std::endl;
    std::cout << "--snr , for signal to noise ratio" << std::endl;
    std::cout << "--psnr , for peek signal to noise ratio" << std::endl;
    std::cout << "--md , for maximum difference" << std::endl;
    return;
}

void brightness_inc(CImg<unsigned char> img, int c, CImg<unsigned char> &result) {
    int N = img._height;
    int n = img._width;
    int z = 0;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < n; j++)
        {
            unsigned int x = i;
            unsigned int y = j;
            int color = img(x, y, z, c);
            color += 50;
            if (color > 255)
            {
                color = 255;
            }
            result(x, y, z, c) = color;
        }
    }
}

void brightness_dec(CImg<unsigned char> img, int c, CImg<unsigned char> &result) {
    int N = img._height;
    int n = img._width;
    int z = 0;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < n; j++)
        {
            unsigned int x = i;
            unsigned int y = j;
            int color = img(x, y, z, c);
            color -= 50;
            if (color < 0)
            {
                color = 0;
            }
            result(x, y, z, c) = color;
        }
    }
}

void contrast(CImg<unsigned char> img, float step, int c, CImg<unsigned char> &result) {
    double factor = (259.0 * (step + 255.0)) / (255.0 * (259.0 - step));
    int N = img.height();
    int n = img.width();
    int z = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < n; j++) {
            unsigned int x = i;
            unsigned int y = j;
            int cont = img(x, y, z, c);
            cont = (factor * (cont - 128)) + 128;
            if (cont > 255)
                cont = 255;
            if (cont < 0)
                cont = 0;
            result(x, y, z, c) = cont;
        }
    }
}

void negative(CImg<unsigned char> img, int c, CImg<unsigned char> &result)
{
    int N = img._height;
    int n = img._width;
    int z = 0;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < n; j++)
        {
            unsigned int x = i;
            unsigned int y = j;
            result(x, y, z, c) =  255 - img(x, y, z, c);
        }
    }
}

int arg_check(int argc, char *argv) {
    std::string commands[16] = {"--help", "--brightness", "--contrast", "--negative", "--hflip",
                                "--vflip", "--dflip", "--shrink", "--enlarge","--alpha",
                                "--gmean", "--mse", "--pmse", "--snr", "--psnr", "--md"};

    bool correct_command = false;
    for (int i = 0; i < 16; i++)
    {
        if (argv == commands[i])
        {
            correct_command = true;
        }
    }
    if (!correct_command)
    {
        std::cout << "There is no command like that. Try --help." << std::endl;
        return 1;
    }

    if (argc <= 1)
    {
        std::cout << "You have to specify arguments. Try --help for help." << std::endl;
        return 1;
    }
    else if (argv == commands[0])    /* commands[0] is help */
    {
        std::cout << "Here is your help" << std::endl;
        help();
        return 2;
    }
    else if ((argv == commands[1]) && (argc < 4))    /* commands[1] is brightness */
    {
        std::cout << "You have passed to little arguments" << std::endl;
        return 1;
    }
    else if ((argv == commands[3]) && (argc < 3))    /* commands[2] is negative */
    {
        std::cout << "You have passed to little arguments" << std::endl;
        return 1;
    }
    return 0;
}

void vflip(CImg<unsigned char> img, int c, CImg<unsigned char> &result)
{
    int h = img._height;
    int w = img._width;
    int z = 0;

    for (int y = 0; y < (h/2); y++) {
        for (int x = 0; x < w; x++) {
                int y2 = h - 1 - y;
                int old_val = img(x, y, z, c);
                result(x, y, z, c) = img(x, y2, z, c);
                result(x, y2, z, c) = old_val;
        }
    }
}

void hflip(CImg<unsigned char> img, int c, CImg<unsigned char> &result) {
    int h = img._height;
    int w = img._width;
    int z = 0;

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < (w/2); x++) {
                int x2 = w - 1 - x;
                int old_val = img(x, y, z, c);
                result(x, y, z, c) = img(x2, y, z, c);
                result(x2, y, z, c) = old_val;
        }
    }
}

void dflip(CImg<unsigned char> img, int c, CImg<unsigned char> &result) {
    int h = img._height;
    int w = img._width;
    int z = 0;

    for (int y = 0; y < (h/2); y++) {
        for (int x = 0; x < w; x++) {
            int y2 = h - 1 - y;
            int old_val = img(x, y, z, c);
            result(x, y, z, c) = img(x, y2, z, c);
            result(x, y2, z, c) = old_val;
        }
    }

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < (w/2); x++) {
            int x2 = w - 1 - x;
            int old_val = result(x, y, z, c);
            result(x, y, z, c) = result(x2, y, z, c);
            result(x2, y, z, c) = old_val;
        }
    }
}

void resize(CImg<unsigned char> img, float delta, int c, CImg<unsigned char> &result) {
    int width = img.width() * delta;
    int height = img.height() * delta;

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
                int pixel = img(x/delta, y/delta, 0,c);
                result(x, y , 0, c) = pixel;
        }
    }
}

void alphaf(CImg<unsigned char> img, CImg<unsigned char> &result, int alpha, int channel) {

    //std::cout << "Startin' the creation of extension" << std::endl;
    const int h = img._height;
    const int w = img._width;
    int z = 0;

    //std::cout << "Allocation of memory for extension" << std::endl;
    unsigned char **extension = new unsigned char*[h + 2];
    for (int i = 0; i < h + 2; ++i) {
        extension[i] = new unsigned char[w + 2];
    }

    //std::cout << "Copying the lines to extension" << std::endl;
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            for (int c = 0; c < 3; ++c) {
                extension[y + 1][x + 1] =  img(x, y, z, channel);
                //  Filling the left and right column
                extension[y + 1][0] = img(0, y, z, channel);
                extension[y + 1][w + 1] = img(w - 1, y, z, channel);
            }
        }
    }

    //std::cout << "Filling the first line of extension" << std::endl;
    memcpy(&extension[0][0], &extension[1][0], (w + 2) * sizeof(unsigned char));

    //std::cout << "Filling the last line of extension" << std::endl;
    memcpy(&extension[h + 1][0], &extension[h][0], (w + 2) * sizeof(unsigned char));

    alphaimp(extension, result, h+2, w+2, alpha, channel);

    //  Free memory of extension
    for (int i = 0; i < h + 2; ++i) {
        delete[] extension[i];
    }
    delete[] extension;
    return;
}

void alphaimp(unsigned char **img, CImg<unsigned char> &result, int h, int w, int alpha, int channel) {
    const int z = 0;
    //  Describing the set
    const int start = (alpha + 1) / 2;
    const int end = 9 - (2 * alpha + 1) / 4;

    //  Moving widow through the image
    for (int x = 1; x < (h - 1); ++x) {
        for (int y = 1; y < (w - 1); ++y) {

            //   Getting the value of image pixels into window
            int window_iterator = 0;
            unsigned char window[9];

            for (int yg = (y - 1); yg < (y + 2); ++yg) {
                for (int xg = (x - 1); xg < (x + 2); ++xg) {
                    window[window_iterator] = img[yg][xg];
                    window_iterator++;
                }
            }

            //  Sorting the window by finding the minimum element
            for (int i = 0; i < 9; ++i) {
                for (int j = 0; j < 8; ++j) {
                    if (window[j] > window[j+1]) {
                        //  Switching
                        unsigned char temp = window[j];
                        window[j] = window[j + 1];
                        window[j + 1] = temp;
                    }
                }
            }

            //  Put the new value in average
            int result_value = 0;
            for (int i = start; i < end; ++i) {
                result_value += window[i];
            }
            result_value /= (9 - alpha);
            result(x-1,y-1,z,channel) = result_value;
        }
    }
    return;
}

void gmean(CImg<unsigned char> img, CImg<unsigned char> &result, int channel) {
    const int h = img._height;
    const int w = img._width;
    const int z = 0;

    //std::cout << "Allocation of memory for extension" << std::endl;
    unsigned char **extension = new unsigned char*[h + 2];
    for (int i = 0; i < h + 2; ++i) {
        extension[i] = new unsigned char[w + 2];
    }

    //std::cout << "Copying the lines to extension" << std::endl;
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            for (int c = 0; c < 3; ++c) {
                extension[y + 1][x + 1] =  img(x, y, z, channel);
                //  Filling the left and right column
                extension[y + 1][0] = img(0, y, z, channel);
                extension[y + 1][w + 1] = img(w - 1, y, z, channel);
            }
        }
    }

    //std::cout << "Filling the first line of extension" << std::endl;
    memcpy(&extension[0][0], &extension[1][0], (w + 2) * sizeof(unsigned char));

    //std::cout << "Filling the last line of extension" << std::endl;
    memcpy(&extension[h + 1][0], &extension[h][0], (w + 2) * sizeof(unsigned char));

    gmeanimp(extension, result, h+2, w+2, channel);

    //  Free memory of extension
    for (int i = 0; i < h + 2; ++i) {
        delete[] extension[i];
    }
    delete[] extension;
    return;
}

void gmeanimp(unsigned char **img, CImg<unsigned char> &result, int h, int w, int channel) {
    const int z = 0;

    //  Moving widow through the image
    for (int x = 1; x < (h - 1); ++x) {
        for (int y = 1; y < (w - 1); ++y) {

            //   Getting the value of image pixels into window
            int window_iterator = 0;
            unsigned char window[9];

            for (int yg = (y - 1); yg < (y + 2); ++yg) {
                for (int xg = (x - 1); xg < (x + 2); ++xg) {
                    window[window_iterator] = img[yg][xg];
                    window_iterator++;
                }
            }

            //  Calculating the geometric mean
            double multip = 1;
            for (int i = 0; i < 9; ++i) {
                multip *= window[i];
            }
            double exponent = 1.0/9.0;
            double geometric_mean = pow(multip, exponent);
            //  Put the value in result
            result(x-1,y-1,z,channel) = geometric_mean;
        }
    }
    return;
}

double mse(CImg<unsigned char> original, CImg<unsigned char> denoise, int c) {
    //  Mean square error
    int width = original.width();
    int height = original.height();
    double sum = 0;

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            for (int color = 0; color < c; ++color) {
                double difference = original(x, y, 0, color) - denoise(x, y, 0, color);
                double square = pow(difference, 2.0);
                sum += square;
            }
        }
    }
    sum /= c;
    double mse = (sum)/(width * height);
    return mse;
}

double pmse(CImg<unsigned char> original, CImg<unsigned char> denoise, int c) {
    //  Peak mean square error
    int width = original.width();
    int height = original.height();
    double sum = 0;
    double max = 0;

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            for (int color = 0; color < c; ++color) {
                if (original(x, y, 0, color) > max) {
                    max = original(x, y, 0, color);
                }
            }
        }
    }

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            for (int color = 0; color < c; ++color) {
                double difference = original(x, y, 0, color) - denoise(x, y, 0, color);
                double square = pow(difference, 2.0);
                sum += square;
            }
        }
    }
    sum /= c;
    double mse = (sum)/(width * height);
    double pmse = mse/max;
    return pmse;
}

double snr(CImg<unsigned char> original, CImg<unsigned char> denoise, int c) {
    //  Signal to noise ratio
    int width = original.width();
    int height = original.height();
    double sum = 0;
    double difference_sum = 0;

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            for (int color = 0; color < c; ++color) {
                double value = original(x, y, 0, color);
                double square = pow(value, 2.0);
                sum += square;
            }
        }
    }

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            for (int color = 0; color < c; ++color) {
                double difference = original(x, y, 0, color) - denoise(x, y, 0, color);
                double square = pow(difference, 2.0);
                difference_sum += square;
            }
        }
    }

    double ratio = sum / difference_sum;
    double snr = 10 * log10(ratio);
    return snr;
}

double psnr(CImg<unsigned char> original, CImg<unsigned char> denoise, int c) {
    //  Peak signal to noise ratio
    int width = original.width();
    int height = original.height();
    double max_sum = 0;
    double difference_sum = 0;
    double max = 0;

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            for (int color = 0; color < c; ++color) {
                if (original(x, y, 0, color) > max) {
                    max = original(x, y, 0, color);
                }
            }
        }
    }

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            for (int color = 0; color < c; ++color) {
                double difference = original(x, y, 0, color) - denoise(x, y, 0, color);
                double square = pow(difference, 2.0);
                difference_sum += square;
                double max_square = pow(max, 2.0);
                max_sum += max_square;
            }
        }
    }

    double ratio = max_sum / difference_sum;
    double psnr = 10 * log10(ratio);
    return psnr;
}

int md(CImg<unsigned char> original, CImg<unsigned char> denoise, int c) {
    // Maximum difference

    int width = original.width();
    int height = original.height();
    int difference = 0;
    int max_dif = 0;

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            for (int c = 0; c < 3; ++c) {
                abs(difference = original(x, y, 0, c) - denoise(x, y, 0, c));
                if (difference > max_dif) {
                    max_dif = difference;
                }
            }
        }
    }
    return max_dif;
}

