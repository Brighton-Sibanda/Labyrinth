# Labyrinth

Specifications:

The game begins when any button or the mouse key is pressed.

1. The player [Class Player] starts off at the bottom left of the grid (screen) still and can move in any direction using the arrow keys (but there will be a wall to the left of the player, so they should start by moving to the right).
2. The player accelerates right and left using the arrow keys and can jump using the up arrow key (the player can also move right and left while in the air).
3. If the player reaches a wall with a certain minimum velocity and is still accelerating towards the wall (i.e. the arrow key pointing towards the wall is pressed), they will be able to slide and jump off it, meaning they become attached to the wall until either the arrow key pointing towards the wall is released or the user presses the up (jump) arrow; this will cause the player to jump diagonally in the opposite direction.
4. There are 2 doors [class door] which, when the player touches would transport them to another grid (i.e. another part of the same level). The other grid has more coins and more treasure.
5. There are 3 types of obstacles [Class Game_element], shooters, arrows (fired by shooters) and spikes. (The number of each obstacle in a level is subjective and depends on the structure and difficulty of the level. It is yet to be determined).
  - Shooters shoot arrows (projectiles) constantly and periodically in the direction that they are pointing. They do not damage the player if touched but only by the means of the arrows they shoot. The player can walk on them.
  - Arrows are projectiles that move in a straight line until they either hit a wall, which would cause them to disappear, or hit the player, which would cause the player to lose a life, lose 5 points, and be transported to the previous starting position.
  - Spikes are stationary obstacles that cause damage to the player only if touched. They cause the player to lose a life, lose 25 points, and be transport to the starting position. 
6. There are 2 types of rewards [Class Game_element], coins and treasure chests that exist along the path which add points to their score.  
  - Coins are distributed all across the level and, when acquired by the player, increase their score by 10 points. (The locations and number of coins are subject to the level structure and difficulty and are yet to be determined).
  - Treasure chests will be placed in hidden parts of the labyrinth or at places difficult to reach and, when acquired, increase the player’s score by 100 points. Each level only has 3 treasure chests. (The locations of the treasure chests are subject to the level structure and difficulty and are yet to be determined).
7. Initially, the player has 4 lives (reflected at the top of the screen) and if they lose all of them, the game ends and the user receives their score. If the player finishes the level (by reaching the trophy) without losing all their lives, they receive 50 points for every life they have remaining. 
8. The goal of the game is to reach the trophy, which will be placed at the end of the labyrinth; once the player touches the trophy, the game ends and their score is calculated.
9. The player’s score depends on the obstacles they hit, the number of coins and treasure chests they accumulate, how long it takes them to finish the level, and the number of lives they have remaining when they get the trophy. 
  -  When the player first starts the level, the number of points they would be able to get starts at 300 and decreases by 5 points per second (so if the player takes longer than 1 minute to finish the level, they receive no bonus points for time). The timer runs until the trophy is reached or the game ends. (It is possible for the player to have negative points).

