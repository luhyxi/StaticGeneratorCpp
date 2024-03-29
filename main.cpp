#include <iostream>
#include "Entities/MDParser.h"

int main()
{
    std::cout << "Hello, World!" << std::endl;
	
	string Path = "/home/luana/CLionProjects/DeGen/Test/index.md";
	
	MDParser::Data data = MDParser::ReadMD(Path);
	
	std::cout <<
	"Data Title = " + data.title + "\n"
	"Data Author = " + data.author + "\n"
	"Data Date = " + data.date + "\n"
	"Data Content = " + data.content + "\n"
	<< std::endl;
	
	MDParser::GenerateHtml("/home/luana/CLionProjects/DeGen/Test/template.html",
						   "/home/luana/CLionProjects/DeGen/output.html", data);
	std::cout << "Done!" << std::endl;
	return 0;
}
