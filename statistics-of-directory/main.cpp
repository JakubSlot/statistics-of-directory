#include <filesystem>  
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

using namespace std;
using namespace filesystem;


int countFiles = 0,countLines = 0, countLinesNonEmpty = 0;
void countFilesOfDirectory(const path& pathToScan) {
    for (auto entry = recursive_directory_iterator(pathToScan); entry != recursive_directory_iterator(); ++entry) {
        if (entry->is_regular_file()) {
            countFiles++;
        }
    }
}
void countLinesOfDirectory(const path& pathToScan) {
    for (auto entry = recursive_directory_iterator(pathToScan); entry != recursive_directory_iterator(); ++entry) {
        if (entry->is_regular_file()) {
            string line;
            ifstream file(entry->path().string());
            while (getline(file, line)) {
                countLines++;
                if (!line.empty())
                    countLinesNonEmpty++;
            }                
            file.close();
        }
    }
}

int main() {
    string p;
    cout << "----- statistics of directory -----" << '\n';
    cout << "Enter a directory path: ";
    getline(cin, p);
    const path pathToShow(p);
    if (!exists(pathToShow)) {
        cout << "directory does not exist";
        return 0;
    }
    auto start = chrono::steady_clock::now();
    thread thr1(countFilesOfDirectory, pathToShow);
    thread thr2(countLinesOfDirectory, pathToShow);
    thr1.join();
    thr2.join();
    cout << "number of files: \t \t" << countFiles << '\n';
    cout << "number of lines(non empty): \t" << countLines << '(' << countLinesNonEmpty << ")\n";
    auto end = chrono::steady_clock::now();
    cout << "elapsed time: " << chrono::duration<double> (end-start).count() << "s\n";
    return 0;
}