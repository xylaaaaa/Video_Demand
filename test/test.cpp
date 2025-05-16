#include <iostream>
#include <sstream>
#include <string>
#include <jsoncpp/json/json.h>
#include <memory>

void serilize()
{
    const char *name = "西小明";
    int age = 19;
    float score[] = {77.5, 99.8};

    Json::Value val;
    val["姓名"] = name;
    val["年龄"] = age;
    val["成绩"].append(score[0]);
    val["成绩"].append(score[1]);

    Json::StreamWriterBuilder swb;
    std::unique_ptr<Json::StreamWriter> sw(swb.newStreamWriter());
    std::stringstream ss;
    int ret = sw->write(val, &ss);
    if (!ret)
    {
        std::cout << "序列化失败" << std::endl;
        return;
    }
    std::cout << ss.str();
}
void unserilize(const std::string &str)
{
    Json::Value val;
    Json::CharReaderBuilder crb;
    std::unique_ptr<Json::CharReader> cr(crb.newCharReader());

    std::string err;
    bool ret = cr->parse(str.c_str(), str.c_str() + str.size(), &val, &err);
    std::cout << val["姓名"] << std::endl;
}
int main()
{
    std::string str = R"({"姓名":"西小明"})";
    unserilize(str);
    return 0;
}
