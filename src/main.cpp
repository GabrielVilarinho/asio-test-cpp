#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#define ASIO_STANDALONE
#include "asio.hpp"
#include "asio/ts/buffer.hpp"
#include "asio/ts/internet.hpp"
#include "lib/lazy.h"

// Since we don't know how much buffer ASIO will demand, a 20kb buffer will do
std::vector<char> vBuffer(24 * 1024);

void handleData(asio::ip::tcp::socket& socket)
{
    socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
        [&](std::error_code error_code_runtime, std::size_t length) {
            if(!error_code_runtime)
            {
                std::cout
                    << std::endl << std::endl
                    << "Read " << length << " bytes"
                    << std::endl << std::endl;

                for (int i = 0; i < length; i++)
                    std::cout << vBuffer[i];

                handleData(socket);
            }
        }
    );
}

int main() {
    std::cout << "src/main.cpp called" << std::endl;

    asio::error_code error_code;

    // ASIO needs a unique space to perform stuff and does it in
    // this space called io_context handles any specific platform
    // requirements
    asio::io_context context;


    // Giving fake tasks to ASIO context not die/close too premature
    asio::io_context::work idleWork(context);

    // Atemporal thread for our context in ASIO
    std::thread thrContext = std::thread([&](){ context.run(); });

    // ASIO needs an endpoint to request a connection see more about
    // it uses a naming convention in namespace referring to the protocol
    // to be more concise, see IP and TCP protocols and network protocols
    // in general to know more!

    // As showed below we're resolving the following namespace:
    //
    // "Use from ASIO the protocol IP, and from IP use the TCP protocol
    // to create an endpoint"
    //
    // endpoint as the door or the destination we're trying to reach
//    const char *endpoint_address = "93.184.216.34"; // www.example.com
//    const char *endpoint_address = "172.217.162.206"; // www.youtube.com Brazil's mirror (SAO PAULO)
    const char *endpoint_address = "51.38.81.49"; //
    asio::ip::tcp::endpoint endpoint(asio::ip::make_address(endpoint_address, error_code), 80);

    // Socket can be described as a doorway or bridge "the means through"
    // we're connecting to our endpoint
    asio::ip::tcp::socket socket1(context);

    // Tell the socket to try a connection
    socket1.connect(endpoint, error_code);

    if (!error_code)
    {
        std::cout << "Connected to \"" << endpoint_address << "\"" << std::endl;
    }
    else
    {
        std::cout << "Failed to connect to \""<< endpoint_address <<"\"" << std::endl
        << "Details:\n" << error_code.message() << std::endl;
    }

    if (socket1.is_open())
    {
        handleData(socket1);
        std::string sRequest =
            "GET /index.html HTTP/1.1\r\n"
            "Host: example.com\r\n"
            "Connection: close\r\n\r\n";

        // asio::ip::tcp::socket (write_some) ->  Sending data to our socket/doorway
        // asio::buffer -> Buffer is just a container of an array of bytes and its length
        socket1.write_some(asio::buffer(sRequest.data(), sRequest.size()), error_code);

        Lazy(5 * 1000);
    }

    return 0;
}