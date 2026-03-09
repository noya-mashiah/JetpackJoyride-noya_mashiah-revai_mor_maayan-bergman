#include "HighScoresManager.h"
#include "Exceptions.h"
#include <fstream>
#include <algorithm>
#include <iostream>

HighScoresManager& HighScoresManager::getInstance()
{
    static HighScoresManager instance;
    return instance;
}

void HighScoresManager::addPlayerScore(const int scoreInMeters)
{
    getInstance().addScore(scoreInMeters);
}

HighScoresManager::HighScoresManager()
{
    loadFromFile();
}

void HighScoresManager::addScore(const int scoreInMeters)
{
    m_currentScore = scoreInMeters;
    m_scores.push_back(scoreInMeters);
    sortScores();

    // Keep only top 100 scores
    if (m_scores.size() > 100)
        m_scores.resize(100);

    saveToFile();
}

std::vector<int> HighScoresManager::getTopScores(int count) const
{
    count = std::min(count, static_cast<int>(m_scores.size()));
    return std::vector<int>(m_scores.begin(), m_scores.begin() + count);
}

int HighScoresManager::getCurrentScore() const
{
    return m_currentScore;
}

bool HighScoresManager::hasScores() const
{
    return !m_scores.empty();
}

void HighScoresManager::sortScores()
{
    std::sort(m_scores.begin(), m_scores.end(), std::greater<int>());
}

void HighScoresManager::loadFromFile()
{
    m_scores.clear();
    std::ifstream file(m_filename);
    
    if (!file.is_open()) return; // File doesn't exist yet

    int score;
    while (file >> score)
        m_scores.push_back(score);

    sortScores(); // present only top five
    file.close();
}

void HighScoresManager::saveToFile()
{
    std::ofstream file(m_filename);

    if (!file.is_open()) {
        throw FileIOException("Could not open high scores file for writing: " + m_filename);
    }

    for (int score : m_scores)
        file << score << std::endl;
    
    file.close();
}
//---------------------------------------------------
int HighScoresManager::getLastScore() const
{
     return m_currentScore; 
}
