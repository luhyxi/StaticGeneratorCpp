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
    struct Data; // Struct of the Markdown document, also has an enum
                 // inside the implementation with the possible data types
    
    
    static Data ReadMD(const string& mdPath);
    static string ReadTemplate(const string& templatePath);
    
	// TODO: static string MakeJson(const string& mdPath);
    static void MakeHtml();


private:
    };


#endif //STATICGENERATOR_MDPARSER_H
