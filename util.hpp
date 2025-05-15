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

namespace aod{
    class FileUtil
    {
    private:
        std::string _name; // 文件路径名称
    public:
        FileUtil(const std::string name):_name(name){}
        bool Exists()
        {
            int ret = access(_name.c_str(), F_OK); // 检测文件是否存在
            if (ret != 0)
            {
                std::cout << "file not exists" << std::endl;
                return false;
            }
            return true;
        }
        size_t Size()
        {
            if (this->Exists() == false)
            {
                return 0;
            }
            struct stat st;
            int ret = stat(_name.c_str(), &st); //获取文件属性
            if (ret != 0)
            {
                std::cout << "get file falied!" << std::endl;
                return 0; 
            }
            return st.st_size;
        }
        bool GetContent(std::string *body) // 读取文件到body中
        {
            std::ifstream ifs;
            ifs.open(_name, std::ios::binary); // 以二进制方式打开文件
            if (ifs.is_open() == false)
            {
                std::cout << "open file falied!" << std::endl;
                return false;
            }
            size_t flen = this->Size();
            body->resize(flen);
            ifs.read(&(*body)[0], flen); // 第一个参数必须要是char*的指针,所以这样可以获取第一个字符的指针
            if (ifs.good() == false)
            {
                std::cout << "read file content failed" << std::endl;
                ifs.close();
                return false;
            }
            ifs.close();
            return true;
        }
        bool SetContent(const std::string body)
        {
            std::ofstream ofs;
            ofs.open(_name, std::ios::binary);
            if (ofs.is_open() == false)
            {
                std::cout << "open file failed" << std::endl;
                return false;
            }
            ofs.write(body.c_str(), body.size());
            if (ofs.good() == false)
            {
                std::cout << "write file content failed" << std::endl;
                ofs.close();
                return false;
            }
            ofs.close();
            return true;
        }

        bool CreateDirectory()
        {
            if (this->Exists())
            {
                return true;
            }
            mkdir(_name.c_str(), 0777);
            return true;
        }
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
                    std::cout << "serilize falied" << std::endl;
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
                    std::cout << "UnSerialize failed" << std::endl;
                    return false;
                }
                return true;
            }
    };
}

#endif