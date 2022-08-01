#include "File.h"
#include <filesystem>
#include <fstream>

namespace pow_fi
{
    void SetFilePath(const std::string& pathname)
    {
        //right-click on engine and change to c++17
        std::filesystem::current_path(pathname);
    }

    std::string GetFilePath()
    {
        return std::filesystem::current_path().string();
    }

    bool FileExists(const std::string& pathname)
    {
        return std::filesystem::exists(pathname);
    }

    bool GetFileSize(const std::string& pathname, size_t& size)
    {
        if (!FileExists(pathname)) return false;
        size = std::filesystem::file_size(pathname);

        return true;
    }

    bool ReadFile(const std::string& pathname, std::string& buffer)
    {
        if (!FileExists(pathname)) return false;

        //get file size and set buffer size
        size_t size;
        GetFileSize(pathname, size);
        buffer.resize(size);

        std::ifstream fstream(pathname);
        fstream.read(buffer.data(), size);
        fstream.close();

        return true;
    }

    bool EditFile(const std::string& pathname, std::string text)
    {
        if (!FileExists(pathname)) return false;
        std::fstream file;

        file.open(pathname, std::ios_base::app | std::ios_base::in);
        if (file.is_open()) {
            file << "Some random text to append." << std::endl;
        }
        return true;
    }

}