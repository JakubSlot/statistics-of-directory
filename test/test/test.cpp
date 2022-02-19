#include "pch.h"
#include <gtest/gtest.h>
#include <filesystem>  
#include <iostream>
#include <fstream>

using namespace std;
using namespace filesystem;

int countFiles, countLines, countLinesNonEmpty;
void countFilesOfDirectory(const path& pathToScan) {
    countFiles = 0;
    for (auto entry = recursive_directory_iterator(pathToScan); entry != recursive_directory_iterator(); ++entry) {
        if (entry->is_regular_file()) {
            countFiles++;
        }
    }
}
void countLinesOfDirectory(const path& pathToScan) {
    countLines = 0;
    countLinesNonEmpty = 0;
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

int lines_1d() {
    countLinesOfDirectory("..\\test\\folder_for_test\\1d");
    return countLines;
}
int lines_ne_1d() {
    countLinesOfDirectory("..\\test\\folder_for_test\\1d");
    return countLinesNonEmpty;
}
int files_1d() {
    countFilesOfDirectory("..\\test\\folder_for_test\\1d");
    return countFiles;
}
int lines_2d() {
    countLinesOfDirectory("..\\test\\folder_for_test\\2d");
    return countLines;
}
int lines_ne_2d() {
    countLinesOfDirectory("..\\test\\folder_for_test\\2d");
    return countLinesNonEmpty;
}
int files_2d() {
    countFilesOfDirectory("..\\test\\folder_for_test\\2d");
    return countFiles;
}
int lines_3d() {
    countLinesOfDirectory("..\\test\\folder_for_test\\3d");
    return countLines;
}
int lines_ne_3d() {
    countLinesOfDirectory("..\\test\\folder_for_test\\3d");
    return countLinesNonEmpty;
}
int files_3d() {
    countFilesOfDirectory("..\\test\\folder_for_test\\3d");
    return countFiles;
}
int lines_testDir() {
    countLinesOfDirectory("..\\test\\folder_for_test");
    return countLines;
}
int lines_ne_testDir() {
    countLinesOfDirectory("..\\test\\folder_for_test");
    return countLinesNonEmpty;
}
int files_testDir() {
    countFilesOfDirectory("..\\test\\folder_for_test");
    return countFiles;
}


TEST(LinesIn1d, check_number_of_lines) {
    EXPECT_EQ(lines_1d(), 27);
}
TEST(LinesNEIn1d, check_number_of_lines_nonempty) {
    EXPECT_EQ(lines_ne_1d(), 27);
}
TEST(FilesIn1d, check_number_of_files) {
	EXPECT_EQ(files_1d(),2);
}
TEST(LinesIn2d, check_number_of_lines) {
    EXPECT_EQ(lines_2d(), 6);
}
TEST(LinesNEIn2d, check_number_of_lines_nonempty) {
    EXPECT_EQ(lines_ne_2d(), 6);
}
TEST(FilesIn2d, check_number_of_files) {
    EXPECT_EQ(files_2d(), 1);
}
TEST(LinesIn3d, check_number_of_lines) {
    EXPECT_EQ(lines_3d(), 28);
}
TEST(LinesNEIn3d, check_number_of_lines_nonempty) {
    EXPECT_EQ(lines_ne_3d(), 27);
}
TEST(FilesIn3d, check_number_of_files) {
    EXPECT_EQ(files_3d(), 2);
}
TEST(LinesInTestDir, check_number_of_lines) {
    EXPECT_EQ(lines_testDir(), 73);
}
TEST(LinesNEInTestDir, check_number_of_lines_nonempty) {
    EXPECT_EQ(lines_ne_testDir(), 69);
}
TEST(FilesInTestDir, check_number_of_files) {
    EXPECT_EQ(files_testDir(), 7);
}

int matn(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}