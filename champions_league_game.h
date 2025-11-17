#ifndef CHAMPIONS_LEAGUE_GAME_H_
#define CHAMPIONS_LEAGUE_GAME_H_

#include <string>
#include <unordered_map>

class ChampionsLeagueGame {
 public:
  ChampionsLeagueGame();

  bool IsValidYear(int year) const;
  bool CheckGuess(int year, const std::string& guess) const;
  std::string GetWinner(int year) const;

  // Helper: returns a small message summary.
  std::string ResultMessage(int year, const std::string& guess) const;

 private:
  std::unordered_map<int, std::string> winners_;

  static std::string ToLower(const std::string& s);
  static std::string Trim(const std::string& s);
};

#endif  // CHAMPIONS_LEAGUE_GAME_H_
