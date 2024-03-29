//
// Created by luana on 3/26/24.
// Class made for parsing a Markdown blog post into an HTML page, conversion to JSON and more

#include <iostream>
#include <fstream>
#include <string>
#include <future>
#include <vector>
#include "MDParser.h"
#include "../Libs/json.hpp"

using json = nlohmann::json;
using std::string;

// Const made for HTML parsing later on
const int titleLine = 12;
const int authorLine = 19;
const int dateLine = 20;
const int contentLine = 22;

/// Used to parse strings in a switch-case
enum PossibleData {
	title = 1, author = 2, date = 3, content = 4,
};

PossibleData HashIt(string const &inString)
{
	if (inString.contains("title")) return title;
	if (inString.contains("author")) return author;
	if (inString.contains("date")) return date;
	else return content;
}

/// Reads the md file and creates a Data struct
MDParser::Data MDParser::ReadMD(const string &mdPath)
{
	std::ifstream mdFile;
	mdFile.open(mdPath);
	
	string line;
	
	if (!mdFile.is_open()) throw std::runtime_error("Error opening file: " + mdPath);
	
	MDParser::Data data;
	while (getline(mdFile, line))
	{
		if (line == "---")
		{
			while (getline(mdFile, line) && line != "---")
			{
				switch (HashIt(line))
				{
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
			while (getline(mdFile, line) && line != "---")
			{
				data.content += line + "\n";
			}
		}
	}
	mdFile.close();
	return data;
}

void MDParser::GenerateHtml(const string &templatePath, const string &outputPath, Data &data)
{
	std::ifstream tmpFile;
	std::ofstream outputFile;
	
	outputFile.open(outputPath);
	if (!outputFile.is_open()) {
		throw std::runtime_error("Error opening output file: " + outputPath);
	}
	
	
	// Read from template and write to output
	tmpFile.open(templatePath);
	if (!tmpFile.is_open()) throw std::runtime_error("Error opening template file: " + templatePath);
	
	MDParser::CopyFiles(tmpFile, outputFile);
	tmpFile.close();
	
	// Open output file for reading to replace content
	outputFile.open(outputPath);
	if (!outputFile.is_open()) throw std::runtime_error("Error opening output file for reading");
	outputFile.close();
	
	ChangeHtmlContent(outputPath, data);
}



///Simple function to copy files
void MDParser::CopyFiles(std::ifstream& original, std::ofstream& destiny)
{
	if (!original.is_open() || !destiny.is_open()) {
		throw std::runtime_error("Error opening files for copying");
	}
	
	destiny << original.rdbuf();
}

void MDParser::ChangeHtmlContent(const std::string htmlPath, Data& data) {
	std::fstream file(htmlPath);  // Open for reading and writing
	
	if (!file.is_open()) {
		// Handle error: couldn't open file for modification
		return;
	}
	
	std::string line;
	int currentLine = 1;
	
	while (getline(file, line)) {
		currentLine++;
		switch (currentLine) {
			case titleLine:
				line = "    <h1><a href=\"#\">" + data.title + "</a></h1>";
				file << line;
				continue;
			case authorLine:
				line = "            <span>" + data.author + "</span>";
				file << line;
				continue;
			case dateLine:
				line = "            on <span>" + data.date + "</span></p>";
				file << line;
				continue;
			case contentLine:
				line = "            <p>" + data.content + "</p>";
				file << line;
				continue;
		}
		continue;
	}
	
	file.close();
}



//void MDParser::MakeHtml()
// TODO: string MDParser::MakeJson(const string &mdPath)
// TODO: std::future<string> AsyncReadMD() = std::async(&ReadMD,MDPath);
