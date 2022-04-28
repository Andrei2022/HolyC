#include <vector>
#include <iostream>
#include <string>
#include <fstream>

int main() {
    //create an array of strings
    std::vector<std::string> v;
    //open the file
    std::ifstream fin("fisier.txt");
    //read the file line by line
    std::string line;
    while (std::getline(fin, line)) {
        //add the line to the array
        v.push_back(line);
    }
    //close the file
    fin.close();
    //print the array

}