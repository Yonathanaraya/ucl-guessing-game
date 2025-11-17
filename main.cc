#include "crow_all.h"
#include "champions_league_game.h"

#include <sstream>
#include <cstdlib>
#include <string>

std::string build_index_page(const ChampionsLeagueGame& game,
                             const std::string& message = "") {
  std::ostringstream html;

  html << "<!doctype html>\n"
          "<html>\n"
          "<head>\n"
          "<meta charset='utf-8'>\n"
          "<title>Champions League Guessing Game</title>\n"
          "<style>\n"
          "    body { font-family: -apple-system, system-ui, sans-serif; "
          "background:#0b1633; color:#f5f5f5; display:flex; "
          "justify-content:center; align-items:center; height:100vh; margin:0; }\n"
          "    .card { background:#111827; padding:24px 32px; border-radius:16px; "
          "box-shadow:0 10px 30px rgba(0,0,0,.5); max-width:420px; width:100%; }\n"
          "    h1 { margin-top:0; font-size:24px; }\n"
          "    label, select, input { display:block; width:100%; margin-bottom:12px; }\n"
          "    input, select { padding:8px 10px; border-radius:8px; border:none; }\n"
          "    button { background:#22c55e; color:#04101f; padding:10px 14px; "
          "border-radius:999px; border:none; cursor:pointer; font-weight:600; "
          "width:100%; }\n"
          "    .message { margin-top:16px; padding:10px 12px; border-radius:8px; "
          "background:#202617; }\n"
          "</style>\n"
          "</head>\n"
          "<body>\n"
          "  <div class='card'>\n"
          "    <h1>Champions League Guessing Game</h1>\n"
          "    <form action='/guess' method='GET'>\n"
          "      <label for='year'>Pick a year:</label>\n"
          "      <select id='year' name='year'>\n";

  int years[] = {2014, 2015, 2016, 2017, 2018,
                 2019, 2020, 2021, 2022, 2023, 2024};

  for (int y : years) {
    html << "        <option value='" << y << "'>" << y << "</option>\n";
  }

  html << "      </select>\n"
          "      <label for='team'>Your guess (team name):</label>\n"
          "      <input id='team' name='team' placeholder='e.g., Real Madrid' />\n"
          "      <button type='submit'>Submit Guess</button>\n"
          "    </form>\n";

  if (!message.empty()) {
    html << "    <div class='message'>" << message << "</div>\n";
  }

  html << "  </div>\n"
          "</body>\n"
          "</html>\n";

  return html.str();
}

int main() {
  crow::SimpleApp app;
  ChampionsLeagueGame game;

  // Home page
  CROW_ROUTE(app, "/")([&game]() {
    crow::response resp(build_index_page(game));
    resp.set_header("Content-Type", "text/html");
    return resp;
  });

  // Guess route: /guess?year=2017&team=Real+Madrid
  CROW_ROUTE(app, "/guess")([&game](const crow::request& req) {
    auto year_str = req.url_params.get("year");
    auto team = req.url_params.get("team");

    std::string message;

    if (!year_str || !team || std::string(team).empty()) {
      message = "Please choose a year and enter a team name.";
    } else {
      int year = std::atoi(year_str);
      message = game.ResultMessage(year, team);
    }

    crow::response resp(build_index_page(game, message));
    resp.set_header("Content-Type", "text/html");
    return resp;
  });

  app.port(18080).multithreaded().run();
}
