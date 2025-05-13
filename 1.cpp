#include <iostream>
#include <sstream>
#include <string>
#include <jsoncpp/json/json.h>
#include <memory>

int main()
{
  const char* name = "西小明";
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
  std::cout << ret << std::endl;
  std::cout << ss.str();
  return 0;
}
