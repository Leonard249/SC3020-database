#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "record.h"
#include "disk.h"
#include "Bplustree.h"
using namespace std;
// Function to read data from the file and store it in a vector of Record
int main()
{
    // initialise disk
    Disk *disk = new Disk(500000000, 400, sizeof(Record));

    // Open the input file
    std::ifstream infile("games.txt");
    if (!infile)
    {
        std::cerr << "Could not open the file!" << std::endl;
        return 1;
    }

    std::string line;

    // Read the headers (first line)
    std::getline(infile, line); // This will just skip the header line

    // Read the subsequent lines (data) into a vector of Records
    std::vector<Record> records;
    int recordnumber = 0;
    while (std::getline(infile, line))
    {
        std::istringstream dataStream(line);
        Record record;
        std::string value;

        // Get each value from the line and store it in the Record struct
        try
        {
            std::getline(dataStream, record.GAME_DATE_EST, '\t');        // First value: GAME_DATE_EST
            std::getline(dataStream, value, '\t');                       // Second value: TEAM_ID_home
            record.TEAM_ID_home = std::stoi(value);                      // Convert to int
            std::getline(dataStream, value, '\t');                       // Third value: PTS_home
            record.PTS_home = std::stoi(value);                          // Convert to int
            std::getline(dataStream, value, '\t');                       // Fourth value: FG_PCT_home
            record.FG_PCT_home = std::stof(value);                       // Convert to float
            std::getline(dataStream, value, '\t');                       // Fifth value: FT_PCT_home
            record.FT_PCT_home = std::stof(value);                       // Convert to float
            std::getline(dataStream, value, '\t');                       // Sixth value: FG3_PCT_home
            record.FG3_PCT_home = std::stof(value);                      // Convert to float
            std::getline(dataStream, value, '\t');                       // Seventh value: AST_home
            record.AST_home = std::stoi(value);                          // Convert to int
            std::getline(dataStream, value, '\t');                       // Eighth value: REB_home
            record.REB_home = std::stoi(value);                          // Convert to int
            std::getline(dataStream, value, '\t');                       // Ninth value: HOME_TEAM_WINS
            record.HOME_TEAM_WINS = static_cast<bool>(std::stoi(value)); // Convert to bool
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Invalid data format in line: " << line << std::endl;
            continue; // Skip this record if there is an error
        }
        catch (const std::out_of_range &e)
        {
            std::cerr << "Number out of range in line: " << line << std::endl;
            continue; // Skip this record if there is an error
        }
        Record *recordPtr = disk->writeRecord(record);
        recordnumber++;
        // Bplustree.insertKey(recordPtr->FG_PCT_home, recordPtr);
        records.push_back(record);
    }

    // task 1

    // Output the records
    std::cout << "Records: " << std::endl;
    for (const auto &record : records)
    {
        std::cout << "Game Date: " << record.GAME_DATE_EST
                  << ", Team ID: " << record.TEAM_ID_home
                  << ", Points: " << record.PTS_home
                  << ", FG%: " << record.FG_PCT_home
                  << ", FT%: " << record.FT_PCT_home
                  << ", FG3%: " << record.FG3_PCT_home
                  << ", Assists: " << record.AST_home
                  << ", Rebounds: " << record.REB_home
                  << ", Home Team Wins: " << (record.HOME_TEAM_WINS ? "Yes" : "No")
                  << std::endl;
    }

    // Wait for user input before closing
    cout << "Experiment 1" << endl;
    cout << "NumberofRecords: " << recordnumber << endl;
    cout << "SizeofRecord: " << sizeof(Record) << "Bytes" << endl;
    std::cout << "Press Enter to continue...";
    std::cin.ignore(); // Ignore any newline character left in the input buffer
    std::cin.get();    // Wait for the user to press Enter

    return 0;
}
