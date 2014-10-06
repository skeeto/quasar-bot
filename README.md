# Automatic Quasar Player

This is a quick and dirty bot that automatically plays
[Quasar](http://masseffect.wikia.com/wiki/Quasar) in Mass Effect. It
doesn't cheat or manipulate the game itself in any way. It reads the
value from the screen and takes the appropriate action by simulating
mouse clicks. Quasar is a flawed game, allowing the player to beat the
house consistently, so running the bot for a while is a virtually
guaranteed credit flow.

Don't tell Doran about this.

It's tuned to my specific screen resolution (1680x1050) and game
resolution (1440x900). The game must be run in windowed mode so that
`GetPixel()` works correctly. The window must be placed as high as
possible with the left edge exactly flush with the left side of the
screen in Windows 7. Other versions of Windows will require adjustment
as the window decoration size is different (I think).
