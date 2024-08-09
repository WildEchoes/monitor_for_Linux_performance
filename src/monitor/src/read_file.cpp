#include "read_flie.h"

monitor::ReadFile::ReadFile(const std::string &name)
    : m_ifs(name)
{
}

monitor::ReadFile::~ReadFile()
{
    m_ifs.close();
}

bool monitor::ReadFile::readLine(std::vector<std::string> *args)
{
    std::string line;
    std::getline(m_ifs, line);

    // 文件结束或者读取到空行
    if(m_ifs.eof() || line.empty()) {
        return false;
    }

    std::istringstream iss(line); // 文件字符串流
    while (!iss.eof())
    {
        // 通过空格分割字符串
        std::string info;
        iss >> info;
        args->push_back(info);
    }
    return true;
}

std::vector<std::string> monitor::ReadFile::getStatsLines(const std::string& statsFile, const int lineCount) {
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
