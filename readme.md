# Game Design

# Problem
I want to implement the simplest game possible in UE4 from ground up. This turned up to the the first commercially successful video game "Pong".
http://www.ponggame.org/

# Concept & Rules
An empty field that represents a table. There are two opposing players controlling two paddles each on their side of the table.
Players have to move paddles to that the ball flying between them never gets outside the screen. When that happens the player that lost the ball loosses the round, and the other player scores one point.

The game end when one of the players loosed 11 balls, that player looses the game, and the other player wins.

During each round the balls starts with moving slowly, and gradually increases the speed over time.

The angle the ball gets reflected off the paddle depends on where the paddle is hit. The reflection angle gets bigger closer to the sides.

# Requirements

	* All graphics retro-style;
	* All objects are actually 3-d objects displayed in a top down view;
	* Simple menu;
	* Simple UI for win/loose;
	* Sounds for menu clicks, win, loose, ball hits;
	* Single-player mode;
	* Hot-seat multi-player mode;
	* 8-bit background music (if possible to find an appropriate license);
	* Controls:
	* 
		* Single-player: Keyboard / Controller / Mouse;
		* Multi-player: Keyboard + Controller / Two Controllers;

# Possible Future Ideas (The NO List)

	* Fancy graphics for the original game;
	* More game modes:
	* 
		* The more you play the better visuals become;
		* 3d Pong;
