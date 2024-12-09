#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

void processRequest(const string& request, string& response) {
    response = "Processed: " + request;
}

void checkRequests() {
    ifstream inFile("f1.txt");
    ofstream outFile("f2.txt", ios::app);
    streampos lastSize = 0;

    while (true) {
        inFile.open("f1.txt", ios::ate);
        streampos currentSize = inFile.tellg();
        inFile.close();

        if (currentSize > lastSize) {
            inFile.open("f1.txt");
            inFile.seekg(lastSize);
            string request;
            while (getline(inFile, request)) {
                string response;
                processRequest(request, response);
                outFile << response << endl;
            }
            lastSize = currentSize;
            outFile.close();
        }
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main() {
    checkRequests();
    return 0;
}
