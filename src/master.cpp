#include <boost/asio.hpp>
#include <thread>
#include "server.hpp"
#include "event.hpp"

int main()
{
    boost::asio::io_context io_context;
    evt_queue eventQueue;
    
    Server s(io_context, 50000, &eventQueue);
    
    std::thread thrd([](boost::asio::io_context* io_context) {
        io_context->run();
    }, &io_context);

    while(true)
    {
        sleep(3);
        std::cout << 123 << "\n";
        continue;
    }
    thrd.join();
    return 0;
}