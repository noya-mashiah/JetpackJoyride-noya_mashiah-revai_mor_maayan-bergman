#pragma once
#include <vector>
#include <string>

/*
* manage the high score screen data
*/

class HighScoresManager {
public:
    static HighScoresManager& getInstance();

    // Static method to add score directly
    static void addPlayerScore(const int scoreInMeters);
    bool hasScores() const;

    std::vector<int> getTopScores(int count = 5) const;
    int getCurrentScore() const;

private:
    HighScoresManager();
    void addScore(const int scoreInMeters);
    void sortScores();
    void loadFromFile();
    void saveToFile();
    int getLastScore() const;
    std::vector<int> m_scores;
    int m_currentScore = 0;
    std::string m_filename = "highscores.txt";
};
