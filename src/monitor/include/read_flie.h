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

    std::vector<std::string> ReadFile::getStatsLines(const std::string& statsFile, const int lineCount) {
        std::vector<std::string> stats_lines;
        std::ifstream buffer(statsFile);

        for (size_t i=0; i<lineCount;++i)
        {
            std::string line;
            std::getline(buffer, line);
            if(line.empty()) {
                break;
            }
            stats_lines.push_back(line);
        }
        
        return stats_lines;
    }
} // namespace monitor



#endif // __READ_FILE_H__