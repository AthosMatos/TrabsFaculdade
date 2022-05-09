#include "App.hpp"
#include <iostream>
#include <fstream>
#include <HTTPRequest.hpp>

int main(void)
{
	App* app = new App;

	app->Init();
	app->Run();

    try
    {
        // you can pass http::InternetProtocol::V6 to Request to make an IPv6 request
        http::Request request{ "http://httpbin.org/ip" };

        // send a get request
        const auto response = request.send("GET");
        std::cout << std::string{ response.body.begin(), response.body.end() } << '\n'; // print the result
    }
    catch (const http::RequestError& e)
    {
        std::cerr << "Request error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    catch (const http::ResponseError& e)
    {
        std::cerr << "Response error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
   
}

