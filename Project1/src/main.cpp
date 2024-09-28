#include "record.h"
#include "block.h"
#include "bplustree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

int main()
{
    std::ifstream infile("games.txt");
    std::string line;
    std::vector<Record> records;

    std::getline(infile, line);

    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        Record record;
        std::string temp;

        std::getline(iss, record.GAME_DATE_EST, '\t');
        std::getline(iss, temp, '\t');
        record.TEAM_ID_home = std::stoi(temp);
        std::getline(iss, temp, '\t');
        record.PTS_home = std::stoi(temp);
        std::getline(iss, temp, '\t');
        record.FG_PCT_home = std::stof(temp);
        std::getline(iss, temp, '\t');
        record.FT_PCT_home = std::stof(temp);
        std::getline(iss, temp, '\t');
        record.FG3_PCT_home = std::stof(temp);
        std::getline(iss, temp, '\t');
        record.AST_home = std::stoi(temp);
        std::getline(iss, temp, '\t');
        record.REB_home = std::stoi(temp);
        std::getline(iss, temp, '\t');
        record.HOME_TEAM_WINS = std::stoi(temp);

        records.push_back(record);
    }

    BPlusTree bptree(4); // try try only

    for (const auto &record : records)
    {
        bptree.insert(record);
    }

    auto start = std::chrono::high_resolution_clock::now();
    auto results = bptree.search(0.5, 0.8);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Search Results:" << std::endl;
    for (const auto &record : results)
    {
        std::cout << "Game Date: " << record.GAME_DATE_EST << ", FG_PCT_home: " << record.FG_PCT_home << std::endl;
    }

    std::cout << "Number of records found: " << results.size() << std::endl;
    std::cout << "Search time: " << elapsed.count() << " seconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    std::vector<Record> linear_results;
    for (const auto &record : records)
    {
        if (record.FG_PCT_home >= 0.5 && record.FG_PCT_home <= 0.8)
        {
            linear_results.push_back(record);
        }
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;

    std::cout << "Brute-force linear scan results:" << std::endl;
    std::cout << "Number of records found: " << linear_results.size() << std::endl;
    std::cout << "Search time: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}
