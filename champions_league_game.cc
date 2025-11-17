#include "champions_league_game.h"

#include <algorithm>
#include <cctype>

ChampionsLeagueGame::ChampionsLeagueGame() {
  // You can add more years if you want
  winners_ = {
      {2014, "Real Madrid"},
      {2015, "Barcelona"},
      {2016, "Real Madrid"},
      {2017, "Real Madrid"},
      {2018, "Real Madrid"},
      {2019, "Liverpool"},
      {2020, "Bayern Munich"},
      {2021, "Chelsea"},
      {2022, "Real Madrid"},
      {2023, "Manchester City"},
      {2024, "Real Madrid"},
  };
}

bool ChampionsLeagueGame::IsValidYear(int year) const {
  return winners_.find(year) != winners_.end();
}

bool ChampionsLeagueGame::CheckGuess(int year,
                                     const std::string& guess) const {
  auto it = winners_.find(year);
  if (it == winners_.end()) return false;

  std::string clean_guess = ToLower(Trim(guess));
  std::string clean_answer = ToLower(Trim(it->second));
  return clean_guess == clean_answer;
}

std::string ChampionsLeagueGame::GetWinner(int year) const {
  auto it = winners_.find(year);
  if (it == winners_.end()) return "";
  return it->second;
}

std::string ChampionsLeagueGame::ResultMessage(int year,
                                               const std::string& guess) const {
  if (!IsValidYear(year)) {
    return "That year is not in the game yet.";
  }

  if (CheckGuess(year, guess)) {
    return "Correct! " + GetWinner(year) + " won the Champions League in " +
           std::to_string(year) + ".";
  }

  std::string winner = GetWinner(year);
  return "Wrong. The winner in " + std::to_string(year) + " was " + winner + ".";
}

std::string ChampionsLeagueGame::ToLower(const std::string& s) {
  std::string result = s;
  std::transform(result.begin(), result.end(), result.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  return result;
}

std::string ChampionsLeagueGame::Trim(const std::string& s) {
  if (s.empty()) return s;

  std::size_t start = 0;
  while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) {
    ++start;
  }

  std::size_t end = s.size();
  while (end > start &&
         std::isspace(static_cast<unsigned char>(s[end - 1]))) {
    --end;
  }

  return s.substr(start, end - start);
}
