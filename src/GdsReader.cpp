#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstring>
#include <cstdint>
#include <json/json.h>

std::vector<int> readStream(std::ifstream& stream) {
    std::vector<int> result;
    try {
        std::vector<uint8_t> rec_data;
        uint16_t rec_size;
        stream.read(reinterpret_cast<char*>(&rec_size), 2);
        rec_size = ntohs(rec_size);
        stream.seekg(1, std::ios::cur);
        uint8_t rec_type;
        stream.read(reinterpret_cast<char*>(&rec_type), 1);
        stream.seekg(1, std::ios::cur);
        uint8_t dat_type;
        stream.read(reinterpret_cast<char*>(&dat_type), 1);
        stream.seekg(1, std::ios::cur);
        std::map<uint8_t, int> dat_size = {{0x00, 1}, {0x01, 1}, {0x02, 2}, {0x03, 4}, {0x04, 4}, {0x05, 8}, {0x06, 1}};
        for (int i = 0; i < (rec_size-4)/dat_size[dat_type]; ++i) {
            std::vector<char> buffer(dat_size[dat_type]);
            stream.read(&buffer[0], dat_size[dat_type]);
            rec_data.insert(rec_data.end(), buffer.begin(), buffer.end());
            stream.seekg(1, std::ios::cur);
        }
        result.push_back(rec_size);
        result.push_back(rec_type);
        result.push_back(dat_type);
        for (auto& byte : rec_data) {
            result.push_back(byte);
        }
        return result;
    } catch (...) {
        return {-1};
    }
}

std::string appendName(const std::vector<int>& record) {
    std::map<int, std::string> name_list = {{0x00, "HEADER"}, {0x01, "BGNLIB"}, {0x02, "LIBNAME"}, {0x03, "UNITS"}, {0x04, "ENDLIB"}, {0x05, "BGNSTR"}, {0x06, "STRNAME"}, {0x07, "ENDSTR"}, {0x08, "BONDARY"}, {0x09, "PATH"}, {0x0A, "SERF"}, {0x0B, "AREF"}, {0x0C, "TEXT"}, {0x0D, "LAYER"}, {0x0E, "DATATYPE"}, {0x0F, "WIDTH"}, {0x10, "XY"}, {0x11, "ENDEL"}, {0x12, "SNAME"}, {0x13, "COLROW"}, {0x15, "NODE"}, {0x16, "TEXTTYPE"}, {0x17, "PRESENTATION"}, {0x19, "STRING"}, {0x1A, "STRANS"}, {0x1B, "MAG"}, {0x1C, "ANGLE"}, {0x1F, "REFLIBS"}, {0x20, "FONTS"}, {0x21, "PATHTYPE"}, {0x22, "GENERATIONS"}, {0x23, "ATTRATABLE"}, {0x26, "ELFLAGS"}, {0x2A, "NODETYPE"}, {0x2B, "PROPATTR"}, {0x2C, "PROPVALUE"}, {0x2D, "BOX"}, {0x2E, "BOXTYPE"}, {0x2F, "PLEX"}, {0x32, "TAPENUM"}, {0x33, "TAPECODE"}, {0x36, "FORMAT"}, {0x37, "MASK"}, {0x38, "ENDMASKS"}};
    return name_list[record[1]];
}

std::vector<int> extractData(const std::vector<int>& record) {
    std::vector<int> data;
    if (record[2] == 0x00) {
        return data;
    } else if (record[2] == 0x01) {
        return data;
    } else if (record[2] == 0x02) {
        for (size_t i = 3; i < record.size(); i += 2) {
            int16_t value;
            memcpy(&value, &record[i], 2);
            data.push_back(ntohs(value));
        }
        return data;
    } else if (record[2] == 0x03) {
        for (size_t i = 3; i < record.size(); i += 4) {
            int32_t value;
            memcpy(&value, &record[i], 4);
            data.push_back(ntohl(value));
        }
        return data;
    } else if (record[2] == 0x04) {
        for (size_t i = 3; i < record.size(); i += 4) {
            float value;
            memcpy(&value, &record[i], 4);
            data.push_back(value);
        }
        return data;
    } else if (record[2] == 0x05) {
        for (size_t i = 3; i < record.size(); i += 8) {
            double value;
            memcpy(&value, &record[i], 8);
            data.push_back(value);
        }
        return data;
    } else {
        for (size_t i = 3; i < record.size(); ++i) {
            data.push_back(record[i]);
        }
        return data;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <inputFile> <outputFile>" << std::endl;
        return 1;
    }
    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    std::vector<std::vector<int>> asciiOut;
    std::ifstream ifile(inputFile, std::ios::binary);
    if (!ifile.is_open()) {
        std::cerr << "Failed to open input file" << std::endl;
        return 1;
    }
    while (ifile.peek() != EOF) {
        auto record = readStream(ifile);
        auto data = extractData(record);
        auto name = appendName(record);
        asciiOut.push_back({name, data});
        std::cout << "[" << name << ", " << data << "]" << std::endl;
        if (record[1] == 0x04) {
            break;
        }
    }
    Json::Value root;
    // Conversion of asciiOut to JSON and writing to outputFile is omitted for brevity
    std::ofstream ofile(outputFile);
    if (!ofile.is_open()) {
        std::cerr << "Failed to open output file" << std::endl;
        return 1;
    }
    ofile << root;
    return 0;
}

