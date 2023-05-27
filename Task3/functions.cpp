#include <iostream>
#include "CImg.h"
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include "functions.h"

using namespace cimg_library;
//typedef bool pixel;
typedef unsigned char pixel;

void create_image(CImg<pixel> &result, int c) {
    /*result.assign(8, 9, 1, 3);
    for (int y = 0; y < 9; ++y) {
        for (int x = 0; x < 8; ++x) {
            result(x, y, 0, c) = 0;
        }
    }

    result(4,1,0, c) = 255;
    result(5,1,0, c) = 255;

    for (int i = 1; i < 7; ++i) {
        result(i, 2, 0, c) = 255;
    }

    for (int i = 4; i < 7; ++i) {
        result(i, 3, 0, c) = 255;
    }

    for (int i = 3; i < 7; ++i) {
        result(i, 4, 0, c) = 255;
    }

    result(3, 5, 0, c) = 255;
    result(5, 5, 0, c) = 255;

    result(2, 6, 0, c) = 255;
    result(3, 6, 0, c) = 255;
    result(5, 6, 0, c) = 255;

    result(4, 7, 0, c) = 255;*/

    const int height = 10;
    const int width = 15;
    result.assign(width, height, 1, result.spectrum());

    CImg<pixel> tempResult;
    tempResult.assign(width, height, 1, result.spectrum());
    tempResult = static_cast<pixel>(0);

    for (int y = 2; y < height-2; ++y) {
        for (int x = 2; x < width-2; ++x) {
            tempResult(x, y, 0, c) = 255;
        }
    }
    equal_two_images(tempResult, result, c);
}

void dilation(CImg<pixel> const &image, CImg<pixel> &result, int c, std::array<bool, 9> window) {
    // Center element must be one
    const int height = image.height();
    const int width = image.width();

    try {
        for (int y = 1; y < (height - 1); ++y) {
            for (int x = 1; x < (width - 1); ++x) {

                int window_iterator = 0;
                if (image(x, y, 0, c) == 255) {
                    for (int yw = (y - 1); yw < (y + 2); ++yw) {
                        for (int xw = (x - 1); xw < (x + 2); ++xw) {
                            if (window.at(window_iterator)) {
                                result(xw, yw, 0, c) = 255;
                            }
                            window_iterator++;
                        }
                    }
                }
            }
        }
    }
    catch (std::out_of_range&) {
        std::cout << "out of range!" << std::endl;
        exit(1);
    }
}

void erosion(CImg<pixel> const &image, CImg<pixel> &result, int c, std::array<bool, 9> window) {
    //  Entire structuring element must fill into the image for the pixel to stay
    const int height = image.height();
    const int width = image.width();

    try {
        for (int y = 1; y < (height - 1); ++y) {
            for (int x = 1; x < (width - 1); ++x) {
                std::vector<int> pixel_values;
                int window_iterator = 0;
                for (int yw = (y - 1); yw < (y + 2); ++yw) {
                    for (int xw = (x - 1); xw < (x + 2); ++xw) {
                        if (window.at(window_iterator)) {
                            if ( !image(xw, yw, 0, c) ) {
                                pixel_values.push_back(0);
                            } else {
                                pixel_values.push_back(255);
                            }
                        }
                        window_iterator++;
                    }
                }
                int min = 255;
                for (int pixel_value : pixel_values) {
                    if (pixel_value < min) {min = pixel_value;}
                }
                result(x, y, 0, c) = min;
            }
        }
    }
    catch (std::out_of_range&) {
        std::cout << "out of range!" << std::endl;
        exit(1);
    }
}

void opening(CImg<pixel> const &image, CImg<pixel> &result, int c, std::array<bool, 9> window) {
    try {
        CImg<pixel> intermediate_result;
        intermediate_result.assign(image._width, image._height, 1, image.spectrum());
        erosion(image, intermediate_result, c, window);
        dilation(intermediate_result, result, c, window);
    }
    catch (std::out_of_range&) {
        std::cout << "out of range!" << std::endl;
        exit(2);
    }
}

void closing(CImg<pixel> const &image, CImg<pixel> &result, int c, std::array<bool, 9> window) {
    try {
        CImg<pixel> intermediate_result;
        intermediate_result.assign(image._width, image._height, 1, image.spectrum());
        for (int x = 0; x < result.width(); ++x) {
            for (int y = 0; y < result.height(); ++y) {
                for (int i = 0; i < image.spectrum(); ++i) {
                    intermediate_result(x,y,0,i) = 0;
                }
            }
        }
        dilation(image, intermediate_result, c, window);
        erosion(intermediate_result, result, c, window);
    }
    catch (std::out_of_range&) {
        std::cout << "out of range!" << std::endl;
        exit(2);
    }
}

void HMT_transformation(CImg<pixel> const &image, CImg<pixel> &result, int c) {
   try {
       std::array<bool, 9> fwindow1 = {true, false, false,
                                      true, false, false,
                                      true, false, false};

       std::array<bool, 9> fwindow2 = {true, true, true,
                                       false, false, false,
                                       false, false, false};

       std::array<bool, 9> fwindow3 = {false, false, true,
                                       false, false, true,
                                       false, false, true};

       std::array<bool, 9> fwindow4 = {false, false, false,
                                       false, false, false,
                                       true, true, true};

       std::array<bool, 9> bwindow = {false, false, false,
                                      false, true, false,
                                      false, false, false};
       mask_flip(bwindow);

       CImg<pixel> erodedImage;
       erodedImage.assign(image._width, image._height, 1, image.spectrum());
       CImg<pixel> dilatedImage;
       dilatedImage.assign(image._width, image._height, 1, image.spectrum());
       std::array<CImg<pixel>, 4> results;
       for (int i = 0; i < 4; ++i) {
           results.at(i).assign(image._width, image._height, 1, image.spectrum());
       }

       //   First time
       erosion(image, erodedImage, c, fwindow1);
       dilation(image, dilatedImage, c, bwindow);
       int resultingValue;
       for (int y = 0; y < image._height; ++y) {
           for (int x = 0; x < image._width; ++x) {
               resultingValue = erodedImage(x, y, 0, c) - dilatedImage(x, y, 0, c);
               if (resultingValue > 0) {
                   resultingValue = 255;
               } else {
                   resultingValue = 0;
               }
               results.at(0)(x, y, 0, c) = resultingValue;
           }
       }
       //   Second time
       erosion(image, erodedImage, c, fwindow2);
       dilation(image, dilatedImage, c, bwindow);
       for (int y = 0; y < image._height; ++y) {
           for (int x = 0; x < image._width; ++x) {
               resultingValue = erodedImage(x, y, 0, c) - dilatedImage(x, y, 0, c);
               if (resultingValue > 0) {
                   resultingValue = 255;
               } else {
                   resultingValue = 0;
               }
               results.at(1)(x, y, 0, c) = resultingValue;
           }
       }
       //   Third time
       erosion(image, erodedImage, c, fwindow3);
       dilation(image, dilatedImage, c, bwindow);
       for (int y = 0; y < image._height; ++y) {
           for (int x = 0; x < image._width; ++x) {
               resultingValue = erodedImage(x, y, 0, c) - dilatedImage(x, y, 0, c);
               if (resultingValue > 0) {
                   resultingValue = 255;
               } else {
                   resultingValue = 0;
               }
               results.at(2)(x, y, 0, c) = resultingValue;
           }
       }
       //   Fourth time
       erosion(image, erodedImage, c, fwindow4);
       dilation(image, dilatedImage, c, bwindow);
       for (int y = 0; y < image._height; ++y) {
           for (int x = 0; x < image._width; ++x) {
               resultingValue = erodedImage(x, y, 0, c) - dilatedImage(x, y, 0, c);
               if (resultingValue > 0) {
                   resultingValue = 255;
               } else {
                   resultingValue = 0;
               }
               results.at(3)(x, y, 0, c) = resultingValue;
           }
       }
       for (int y = 0; y < image.height(); ++y) {
           for (int x = 0; x < image.width(); ++x) {
               if (results.at(0)(x, y, 0, c) || results.at(1)(x, y, 0, c) ||
                   results.at(2)(x, y, 0, c) || results.at(3)(x, y, 0, c)) {
                   result(x, y, 0, c) = 255;
               } else {
                   result(x, y, 0, c) = 0;
               }
           }
       }
   }
   catch (std::out_of_range&) {
       std::cout << "out of range!" << std::endl;
       exit(2);
   }
}

void mask_flip(std::array<bool, 9> array) {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < (3/2); x++) {
            int x2 = 3 - 1 - x;
            int old_val = array.at(x + 3 * y);
            array.at(x + 3 * y) = array.at(x2 + 3 * y);
            array.at(x2 + 3 * y) = old_val;
        }
    }
}

void skeleton(CImg<pixel> const &image, CImg<pixel> &result, int c, std::array<bool, 9> window) {
    //  M7

    CImg<pixel> eroded;
    eroded.assign(image._width, image._height, 1, image.spectrum());
    eroded = static_cast<pixel>(0);

    CImg<pixel> opened;
    opened.assign(image._width, image._height, 1, image.spectrum());
    opened = static_cast<pixel>(0);

    CImg<pixel> beforeErosion;
    beforeErosion.assign(image._width, image._height, 1, image.spectrum());

    CImg<pixel> sumOfDifferences;
    sumOfDifferences.assign(image._width, image._height, 1, image.spectrum());

    for (int i = 0; i < image.spectrum(); ++i) {
        opening(image, opened, i, window);
    }

    sumOfDifferences = image - opened;
    beforeErosion = image;

    int k = 0;
    while (is_not_empty(opened)) {
        eroded = static_cast<pixel>(0);
        opened = static_cast<pixel>(0);
        for (int i = 0; i < image.spectrum(); ++i) {
            erosion(beforeErosion, eroded, i, window);
        }
        for (int i = 0; i < image.spectrum(); ++i) {
            opening(eroded, opened, i, window);
        }

        sumOfDifferences += eroded - opened;
        beforeErosion = eroded;

        std::cout << k << " : ";
        k++;
    }
    result = sumOfDifferences;

}
bool is_not_empty(CImg<pixel> const &img) {
    return img != 0;
}
void equal_two_images(const CImg<pixel> &image, CImg<pixel> &result, int c) {
    const int h = image.height();
    const int w = image.width();
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            result(x, y, 0, c) = image(x, y, 0, c);
        }
    }
}

void growing(CImg<pixel> &image, CImg<pixel> &result, int userX, int userY, int condition) {
    int max = image(userX, userY, 0, 0) + condition/2;
    int min = image(userX, userY, 0, 0) - condition/2;
    if (max > 255)
        max=255;
    if (min < 0)
        min=0;
    recursiveGrowing(image, result, userX, userY, max, min);
}
void recursiveGrowing (CImg<pixel> &image, CImg<pixel> &result, int x, int y, int max, int min ) {
    //  Marking pixel red
    result(x, y, 0, 0) = 255;

    //  Recurse left
    x = x - 1;
    if (x >= 0 && x <= 512 && y >= 0 && y <= 512 && image(x, y, 0, 0) > min && image(x, y, 0, 0) < max) {
        if (result(x, y, 0, 0) != 255) {
            recursiveGrowing(image, result, x, y, max, min);
        }
    }
    //  Recurse right
    x = x + 2;
    if (x >= 0 && x <= 512 && y >= 0 && y <= 512 && image(x, y, 0, 0) > min && image(x, y, 0, 0) < max) {
        if (result(x, y, 0, 0) != 255) {
            recursiveGrowing(image, result, x, y, max, min);
        }
    }
    //  Recurse up
    x = x - 1;
    y = y - 1;
    if (x >= 0 && x <= 512 && y >= 0 && y <= 512 && image(x, y, 0, 0) > min && image(x, y, 0, 0) < max) {
        if (result(x, y, 0, 0) != 255) {
            recursiveGrowing(image, result, x, y, max, min);
        }
    }
    //  Recurse down
    y = y + 2;
    if (x >= 0 && x <= 512 && y >= 0 && y <= 512 && image(x, y, 0, 0) > min && image(x, y, 0, 0) < max) {
        if (result(x, y, 0, 0) != 255) {
            recursiveGrowing(image, result, x, y, max, min);
        }
    }
}
