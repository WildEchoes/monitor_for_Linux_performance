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
        std::string info;
        iss >> info;
        args->push_back(info);
    }
    return true;
}
