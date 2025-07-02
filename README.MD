EXCEPTION.HPP:
The first file that was created was to take into account the exceptions that could come up. The base file is the Illegal
move exception that deals with all of the moves that could be considered "illegal" like an empty pit or a pit that is 
out of range. All of the other exceptions are inherited from the base IllMoveException. In the same way, the 
InputException class is the base exception from which the other exceptions are inherited. This class deals with the 
user input, such as when they want to quit or if the user loses connection. The other changes implemented for this file
to work were in Kalah.cpp where we thrw InvalidException() and EmptyException() in order to ensure that the move was
actually valid before performing doMove(). in Game.cpp, we actually implemented the catching of the input errors where
we make sure that the user input is actually valid before letting doMove() perform the move. 

SNAPSHOT.HPP:
The hpp file for snapshot is the header file and declares the Snapshot class where it includes the default constructor,
which intitializes an empty snapshot so that we are able to restore a game if we are finaly given a state file to begin
the game with. It also includes the print and read functions that put the kalah date into an out file and then
eventually will read it into the game.

SNAPSHOT.CPP:
In this file we actually implement the functions in order for snapshot to actually work. I created a default constructor
that creates a default snapshot in the meantime while we actually read in our snapshot to initialize. Once we actually
have our kalah object from the state file, we can actually populate the seeds vector with the information from the file.

TEST FILES:
The first test file we have it pitDNE.in and pitDNEtest.out. This tests when the pit does not exist, both in the fact
that the pit entered is not numerical or if the pit does not exist within the number of houses. The exception is thrown
accordingly and the message displays until the user enters a valid pit. In the same way, pitempty.in and pitemptytest.out
throw the correct exception when the user tries to input an empty pit. Similarly, when a user inputs 'q', this acts as
a QuitException, which is done correctly as the user is shown the quitting message and is told that the game has been
saved. In order to test out the restore feature, restore.out shows the correct intilization of a saved game of the
pitempty.in file. So after, pitempty.in, by doing kalah -r, we are shown the correct positions and board intitialization
after we quit in pitempty.in where it is North's turn! If we try to restore when the file does not exist or we could not
open the file, restoreDNE.out shows the correct exception thrown when we cannot restore a game. As we can see, all of
the features work accordingly thanks to the exceptions!   

In order to run game, you must also enter the number of pits (first argument) and the number of seeds in each pit.