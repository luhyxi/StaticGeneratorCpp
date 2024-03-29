//
// Created by luana on 3/26/24.
//

#ifndef STATICGENERATOR_MDPARSER_H
#define STATICGENERATOR_MDPARSER_H


#include <string>

using std::string;

class MDParser
    {
public:
	
	// Struct of the Markdown document, also has an enum
	// inside the implementation with the possible data types
    struct Data{
		std::string title;
		std::string author;
		std::string date;
		std::string content;
	};;
    
    
    static Data ReadMD(const string& mdPath);
    static void GenerateHtml(const string &templatePath, const string &outputPath, Data &data);
	
private:
	static void CopyFiles(std::ifstream& original, std::ofstream& destiny);
	static void ChangeHtmlContent(const std::string htmlPath, Data &data);
	// TODO: static string MakeJson(const string& mdPath);
    //static void MakeHtml();


private:
    };


#endif //STATICGENERATOR_MDPARSER_H
