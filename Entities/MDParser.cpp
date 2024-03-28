//
// Created by luana on 3/26/24.
//

#include <iostream>
#include <fstream>
#include <string>
#include <future>
#include <vector>
#include "MDParser.h"
#include "../Libs/json.hpp"

using json = nlohmann::json;
using std::string;

///Class made for parsing a Markdown blog post into an HTML page, conversion to JSON and more

struct MDParser::Data {
	string title;
	string author;
	string date;
	string content;
};

/// Used to parse strings in a switch-case
enum PossibleData {
	title = 1, author = 2, date = 3, content = 4,
};

PossibleData HashIt(string const &inString) {
	if (inString.contains("title")) return title;
	if (inString.contains("author")) return author;
	if (inString.contains("date")) return date;
	else return content;
}

/// Reads the md file and creates a Data struct
MDParser::Data MDParser::ReadMD(const string &mdPath) {
	std::ifstream mdFile;
	mdFile.open(mdPath);
	
	string line;
	
	if (!mdFile.is_open()) {
		throw std::runtime_error("Error opening file: " + mdPath);
	}
	
	MDParser::Data data;
	while (getline(mdFile, line)) {
		if (line == "---") {
			while (getline(mdFile, line) && line != "---") {
				switch (HashIt(line)) {
					case title:
						data.title = line.substr(5, line.size() - 5);
						break;
					case author:
						data.author = line.substr(8, line.size() - 8);
						break;
					case date:
						data.date = line.substr(6, line.size() - 6);
						break;
				}
			}
			while (getline(mdFile, line) && line != "---") {
				data.content += line + "\n";
			}
		}
	}
	return data;
}

string MDParser::ReadTemplate(const string &templatePath)
{
	return std::string();
}


void MDParser::MakeHtml()
{
}


// TODO: string MDParser::MakeJson(const string &mdPath)
// TODO: std::future<string> AsyncReadMD() = std::async(&ReadMD,MDPath);
