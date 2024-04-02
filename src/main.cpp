#include <iostream>
#include <string>
#include <regex>
#include <BmpReader.cpp>
#include <GdsReader.cpp>
#include <FindContour.cpp>
#include <SplineInterpolation.cpp>
#include <MaxDeviation.cpp>
#include <Threshold.cpp>
#include <SymmetricDifference.cpp>
#include <gdspy.h>
#include <matplot/matplot.h>
#include <thread>

bool isCorrectBMP(const std::string& fileName) {

    if (std::regex_match(fileName,std::regex("^[a-zA-Z0-9а-яА-ЯёЁ_-]+\.(bmp)$"))) {
        return true; 
    }
    else {
        return false; 
    }
}

bool isCorrectGDS(const std::string& fileName) {

    if (std::regex_match(fileName, std::regex("^[a-zA-Z0-9а-яА-ЯёЁ_-]+\.(gds)$"))) {
        return true; 
    }
    else {
        return false;
    }
}

void exit() {
    std::cout<<"Goodbye!";
    return;
} 

int main() {
    system("chcp 1251");

    std::string gds_file;
    std::string bmp_file;
    bool check_bmp = false;
    bool check_gds = false;
    bool flag = true;
    double h;
    bool check_h = false;

    std::cout << "SWHL_Module Comparison";
    std::cout << "Hello, user!";

    while(true) {
        std::cout << "Before start, put files into the 'examples' directory";
        std::cout << "Please, enter the file name and its extension without additional characters and spaces";
        std::cout << "or exit for finish";

        while(!check_bmp) {
            std::cout << "Enter the first file name with bmp format...";
            std::cin>>bmp_file;

            if(bmp_file == "exit") {
                exit();
                return 0;
            }
            else {
                if (isCorrectBMP(bmp_file)) {               
                    std::cout << bmp_file << " is secure and has the correct extension.\n";
                    check_bmp = true;
                }
                else {
                    std::cout << bmp_file << " is NOT secure or has an incorrect extension.\n";
                    std::cout << "Try again";
                }
            }
        }
        
        while(!check_gds) {
            std::cout << "Enter the second file name with gds format...";
            std::cin>>gds_file;

            if(bmp_file == "exit") {
                exit();
                return 0;
            }
            else {
                if (isCorrectGDS(gds_file)) {               
                std::cout << gds_file << " is secure and has the correct extension.\n";
                check_gds = true;
                }
                else {
                    std::cout << gds_file << " is NOT secure or has an incorrect extension.\n";
                    std::cout << "Try again";
                }
            }   
        }

        std::string filepath_bmp = "example\\" + bmp_file; 
        std::string filepath_gds = "example\\" + gds_file;

        std::vector<std::vector<double>>img = BmpReader(filepath_bmp, flag);
        
        if(flag == false) {
            std::cout<<"BMP file not found or an incorrect name was entered";
            return {};
        }

        std::map<std::pair<int, int>, std::vector<gdspy::Polygon*>> polygons = GdsReader(filepath_gds);
        
        int height = img.size();
        int width = img[0].size();
        bicubicInterpolate2D(img, height * 3, int width * 3);

        while(!check_h) {
            std::cout<<"Input h threshold in range (0, 255)";
            std::cin>>h;
            if(h<0 or h >255) {
                std::cout<< "Impossible threshold";
                std::cout<< "Try again";
            }
            else check_h = !check_h;
        }
        
        binarizeImage(img, h);

    }   
}