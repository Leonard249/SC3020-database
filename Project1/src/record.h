#ifndef RECORD_H
#define RECORD_H

#include <string>

struct Record
{
    std::string GAME_DATE_EST;
    int TEAM_ID_home;
    int PTS_home;
    float FG_PCT_home;
    float FT_PCT_home;
    float FG3_PCT_home;
    int AST_home;
    int REB_home;
    bool HOME_TEAM_WINS;
    void print() const
    {
        std::cout << "GAME_DATE_EST: " << GAME_DATE_EST << ", "
                  << "TEAM_ID_home: " << TEAM_ID_home << ", "
                  << "PTS_home: " << PTS_home << ", "
                  << "FG_PCT_home: " << FG_PCT_home << ", "
                  << "FT_PCT_home: " << FT_PCT_home << ", "
                  << "FG3_PCT_home: " << FG3_PCT_home << ", "
                  << "AST_home: " << AST_home << ", "
                  << "REB_home: " << REB_home << ", "
                  << "HOME_TEAM_WINS: " << HOME_TEAM_WINS << std::endl;
    };
};

#endif
