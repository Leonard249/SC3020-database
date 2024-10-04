#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
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

    // Counter
    int recordnumber = 0;
    int invalidrec = 0;

    // Initialise B+ Tree with max node of 5

    Bplustree tree = Bplustree(4);
    // Read the subsequent lines (data) into a vector of Records

    std::vector<Record> records;
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
            // cout << "record" << endl;
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "Invalid data format in line: " << line << std::endl;
            invalidrec++;
            continue; // Skip this record if there is an error
        }
        catch (const std::out_of_range &e)
        {
            std::cout << "Number out of range in line: " << line << std::endl;
            continue; // Skip this record if there is an error
        }

        Record *recordPtr = (*disk).writeRecord(record);
        // cout << "inserting..." << endl;
        tree.insertKey(record.FG_PCT_home, recordPtr);
        // cout << "insertcomplete" << endl;
        recordnumber++;
        // cout << recordnumber << endl;
        //  records.push_back(record);
    }
    /*
    // Output the records
    std::cout << "Records: " << std::endl;
    for (const auto& record : records) {
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
    */
    // Wait for user input before closing
    std::cout << "Number of invalid Record: " << invalidrec << std::endl;

    // Task 1
    std::cout << "===========================================================================" << std::endl;
    std::cout << "Task 1:" << std::endl;
    std::cout << "Number of records: " << recordnumber << std::endl;
    std::cout << "Size of a record: " << sizeof(Record) << " bytes" << std::endl;
    std::cout << "Number of records stored in a block: " << disk->getBLockMaxRecords() << std::endl;
    std::cout << "Number of blocks used to store data in the disk: " << disk->getNumberOfBlocks() << std::endl;
    std::cout << "===========================================================================" << std::endl;

    // Task 2
    std::cout << "===========================================================================" << std::endl;
    std::cout << "Task 2:" << std::endl;
    std::cout << "Number of Nodes: " << NumberofNodes << endl;
    std::cout << "Number of Levels: " << layers << endl;
    std::cout << "Root Node Keys: " << endl;
    for (size_t i = 0; i < tree.root->keys.size(); ++i)
    {
        std::cout << tree.root->keys[i] << " , "; // Access elements using the index
    }
    cout << endl;
    std::cout << "===========================================================================" << std::endl;

    // Task 3
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<Record> results = tree.searchKey(0.500, 0.800);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Results: " << endl;

    /*for (const auto &record : results)
    {
        std::cout << "Game Date: " << record.GAME_DATE_EST
                  << ", Team ID: " << record.TEAM_ID_home
                  << ", Points: " << record.PTS_home
                  << ", FG%: " << record.FG_PCT_home
                  << std::endl;
    }
    */
    // Time Track for Bruteforce
    auto start2 = std::chrono::high_resolution_clock::now();
    int blockAccesedB = disk->linearScan();
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed2 = end2 - start2;

    cout << "number of results: " << results.size() << endl;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;
    std::cout << "NumberofIO:" << NumberofIO << endl;
    std::cout << "Number Of Data Block accessed through brute force: " << blockAccesedB << endl;
    std::cout << "Elapsed time (Brute Force) : " << elapsed2.count() << " seconds" << std::endl;
    std::cout << "Press Enter to continue...";
    std::cin.ignore(); // Ignore any newline character left in the input buffer
    std::cin.get();    // Wait for the user to press Enter

    return 0;
}
