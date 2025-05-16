#ifndef __MY_UTIL__
#define __MY_UTIL__
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <string>
#include <unistd.h>
#include <sys/stat.h>
#include <jsoncpp/json/json.h>

namespace aod
{
    class FileUtil
    {
    private:
        std::string _name; // 文件路径名称
    public:
        FileUtil(const std::string name) : _name(name) {}
        bool Exists()
        {
            // access的F_OK专门用于检测文件是否存在--- 存在则返回0
            int ret = access(_name.c_str(), F_OK);
            if (ret != 0)
            {
                std::cout << "file is not exists\n";
                return false;
            }
            return true;
        } // 判断文件是否存在
        size_t Size()
        {
            if (this->Exists() == false)
            {
                return 0;
            }
            struct stat st;
            // stat接口用于获取文件属性，其中 st_size就是文件大小成员
            int ret = stat(_name.c_str(), &st);
            if (ret != 0)
            {
                std::cout << "get file stat failed!\n";
                return 0;
            }
            return st.st_size;
        } // 获取文件大小
        bool GetContent(std::string *body)
        {
            std::ifstream ifs;
            ifs.open(_name, std::ios::binary);
            if (ifs.is_open() == false)
            {
                std::cout << "open file failed!\n";
                return false;
            }
            size_t flen = this->Size();
            body->resize(flen);
            ifs.read(&(*body)[0], flen);
            if (ifs.good() == false)
            {
                std::cout << "read file content failed!\n";
                ifs.close();
                return false;
            }
            ifs.close();
            return true;
        } // 读取文件数据到body中
        bool SetContent(const std::string &body)
        {
            std::ofstream ofs;
            ofs.open(_name, std::ios::binary);
            if (ofs.is_open() == false)
            {
                std::cout << "open file failed!\n";
                return false;
            }
            ofs.write(body.c_str(), body.size());
            if (ofs.good() == false)
            {
                std::cout << "write file content failed!\n";
                ofs.close();
                return false;
            }
            ofs.close();
            return true;
        } // 向文件写入数据
        bool CreateDirectory()
        {
            if (this->Exists())
            {
                return true;
            }
            mkdir(_name.c_str(), 0777);
            return true;
        } // 针对目录时创建目录
    };
    class JsonUtil
    {
    public:
        static bool Serialize(const Json::Value &value, std::string *body)
        {
            Json::StreamWriterBuilder swb;
            std::unique_ptr<Json::StreamWriter> sw(swb.newStreamWriter());

            std::stringstream ss;
            int ret = sw->write(value, &ss);
            if (ret != 0)
            {
                std::cout << "Serialize failed!\n";
                return false;
            }
            *body = ss.str();
            return true;
        }
        static bool UnSerialize(const std::string &body, Json::Value *value)
        {
            Json::CharReaderBuilder crb;
            std::unique_ptr<Json::CharReader> cr(crb.newCharReader());

            std::string err;
            bool ret = cr->parse(body.c_str(), body.c_str() + body.size(), value, &err);
            if (ret == false)
            {
                std::cout << "UnSerialize failed!\n";
                return false;
            }
            return true;
        }
    };
}

#endif