#include "server.hpp"

void FileTest()
{
    aod::FileUtil("./www").CreateDirectory();
    aod::FileUtil("./www/index.html").SetContent("<html></html>");
    std::string body;
    aod::FileUtil("./www/index.html").GetContent(&body);
    std::cout << body << std::endl;
    std::cout << aod::FileUtil("./www/index.html").Size() << std::endl;
}
void JsonTest()
{
    Json::Value val;
    val["姓名"] = "小张";
    val["年龄"] = 18;
    val["性别"] = "男";
    val["成绩"].append(77.5);
    val["成绩"].append(87.5);
    val["成绩"].append(97.5);

    std::string body;
    aod::JsonUtil::Serialize(val, &body);
    std::cout << body << std::endl;

    Json::Value stu;
    aod::JsonUtil::UnSerialize(body, &stu);
    std::cout << stu["姓名"].asString() << std::endl;
    std::cout << stu["性别"].asString() << std::endl;
    std::cout << stu["年龄"].asString() << std::endl;
    for (auto &a : stu["成绩"])
    {
        std::cout << a.asFloat() << std::endl;
    }
}
void DataTest()
{
    aod::TableVideo tb_video;
    Json::Value video;
    video["name"] = "变形金刚";
    video["info"] = "这是一个会变形的机器人，机器人大战，精彩纷呈~!";
    video["video"] = "/video/robot.ma4";
    video["image"] = "/image/robot.jpg";

    tb_video.Insert(video);
    tb_video.Update(2, video);
    tb_video.SelectAll(&video);
    tb_video.SelectOne(1, &video);
    tb_video.SelectLike("金刚", &video);
    std::string body;
    aod::JsonUtil::Serialize(video, &body);
    std::cout << body << std::endl;
    tb_video.Delete(1);
}
void ServerTest()
{
    aod::Server server(9090);
    server.RunModule();
}
int main()
{
    // FileTest();
    // JsonTest();
    // DataTest();
    ServerTest();
    return 0;
}