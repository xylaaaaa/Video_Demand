#include "./httplib.h"
#include <iostream>
#include <string>
using namespace std;
int main()
{
    httplib::Server svr;
    svr.Get("/hi", [](const httplib::Request &req, httplib::Response &res)
            {
        // cout<<res.status<<endl;
        // cout<<res.body<<endl;
        // for(auto& x:req.headers)
        // {
        //     cout<<x.first<<" : "<<x.second<<endl;
        // }
        std::string body = "<h1>HelloWorld</h1>";
        res.set_content(body, "text/html");
        res.status = 200; });
    svr.listen("0.0.0.0", 8082);
    return 0;
}