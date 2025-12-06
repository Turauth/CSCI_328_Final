#pragma once
using namespace std;
#include <string>
#include <iostream>

// Define class Data to contain file data and metadata functionality.
class File{
    public:
        string m_name{};
        time_t m_creationTime{};
        string m_location{};
        string m_contents{};

        // Make a constructor which returns a file with its metadata and contents as parameters.
        File(string name, time_t creationTime, string location, string contents)
            : m_name{ name }
            , m_creationTime{ creationTime }
            , m_location{ location }
            , m_contents{ contents } {}
};