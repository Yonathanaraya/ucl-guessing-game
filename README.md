# ucl-guessing-game
Guess the Champions League Winners
What I Did in This Project
This project is a small web app written in C++.
You pick a Champions League year, type a team, and the program tells you if you’re right.
The whole thing runs through the Crow web framework.
How I Set Everything Up
1. Added Crow Manually
Crow doesn’t come with the old crow_all.h anymore.
I had to download the header file myself and put it in the project folder so the include works.
2. Fixed Crow Errors
Crow was not updated for newer Boost versions.
Some functions were removed, so the file didn’t compile.
I replaced Crow’s old SocketAdaptor with a working version.
This fix let the server run and accept requests.
3. Built the HTML Page in C++
Crow returns strings, so I created the whole HTML page using a string builder.
The page has a simple form, dropdown for years, an input box, and a button.
It also shows a message after you guess.
4. Set the Correct Content Type
The browser wasn’t showing the page correctly.
I had to return the HTML like this:
crow::response resp(build_index_page(game));
resp.set_header("Content-Type", "text/html");
return resp;

This makes the browser treat the response as HTML.
How You Build It
Run this:
g++ -std=c++17 main.cc champions_league_game.cc -pthread -o ucl_game

Then run:
./ucl_game

The server will start.
How You Open the App
The terminal shows the port:
0.0.0.0:18080

In Codespaces, you open the forwarded link for port 18080.
That shows the UI in your browser.
How the Game Works
You pick a year.
You type a team name.
The backend checks your guess with a simple map of winners.
It returns a short message saying if you’re right or not.
The page refreshes with the message.
Files I Used


main.cc – handles routes and builds the HTML page


champions_league_game.cc – the game logic


champions_league_game.h – header for the class


crow_all.h – the Crow framework


ucl_game – the compiled file


Skills I Used


basic C++17


handling HTTP with Crow


sending HTML from C++


debugging Boost and Crow issues


running a C++ web server


using Git to track everything
