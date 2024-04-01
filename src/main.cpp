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

        std::vector<std::vector<double>>img = BmpReader(filepath_bmp);
        std::vector<Point> vertices = GdsReader(filepath_gds);


    }   
}