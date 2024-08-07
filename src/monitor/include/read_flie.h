#ifndef __READ_FILE_H__
#define __READ_FILE_H__

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

namespace monitor {
    class ReadFile {
    public:
        explicit ReadFile(const std::string& name);
        virtual ~ReadFile();

        bool readLine(std::vector<std::string> *args);
        static std::vector<std::string> getStatsLines(const std::string& statsFile, const int lineCount);
    
    private:
        std::ifstream m_ifs;
    };
} // namespace monitor

#endif // __READ_FILE_H__