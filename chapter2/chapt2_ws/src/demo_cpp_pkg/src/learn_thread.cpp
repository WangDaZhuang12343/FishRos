#include "iostream"
#include "thread" //多线程
#include "chrono" //时间相关
#include "functional" //函数包装器
#include "cpp-httplib/httplib.h" //下载相关

class Download
{
private:
    /* data */
public:
    void download(const std::string &  host,
                  const std::string & path,
                  const std::function<void(const std::string&,const std::string&)> &callback_world_count)
        {
            std::cout<< "线程" << std::this_thread::get_id() << std::endl;
            httplib::Client client(host);
            auto response = client.Get(path);
            if (response && response -> status == 200){
                callback_world_count(path,response -> body);
            }
        };
    void start_download(const std::string &  host,
                        const std::string &  path,
                        const std::function<void(const std::string&,const std::string&)> &callback_world_count)
        {
            auto download_fun = std::bind(&Download::start_download,this,std::placeholders::_1,
            std::placeholders::_2,std::placeholders::_3);
            std::thread thread(download_fun,host,path,callback_world_count);
            thread.detach();
        };
};

int main()
{
    auto d = Download();
    auto world_count = [](const std::string &path, const std::string &result) -> void
    {
        std::cout<< "下载完成" << path << result.length() <<"->" << result.substr(0,9) <<
        std::endl ;
    };

    d.start_download("http://127.0.0.1:8000","/nove1.txt",world_count);
    d.start_download("http://127.0.0.1:8000","/nove1.txt",world_count);
    d.start_download("http://127.0.0.1:8000","/nove1.txt",world_count);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000*10)); 
    
    return 0;
}

