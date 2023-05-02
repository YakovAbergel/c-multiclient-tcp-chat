# TCP-chatroom

ChatServer is my first big project, I did it together with a school friend and it lasted a week.

The project simulates many chat rooms between clients connected to the server (which runs in the background without interruption) by using TCP (the project also uses UDP).

I will briefly explained what options the user has when the server is running in the background...
When the user connects to the server, an initial page appears with 3 options:
1. Registration
2. Login
3. Exiting the server completely (the user exits but the server still continues to operate)

**You cannot register with the same name twice.
**You cannot connect with a username that is not registered on the server.
**You cannot log in with an incorrect password.

After connecting to the server, a second page appears with these options:
1. Create a new group
2. Join an existing group
3. Leave a group
4 Log out and return to the initial screen

*You cannot join a group that does not exist.
*Once all users leave an existing group then it is deleted.
*By disconnecting from the server, the user automatically leaves all the groups he was in.

Remarks:
To run the project you need to go into the "ServerManagement" folder, open the terminal and create a run file using make and after that run the run file for the server to run.
In addition, every user who wants to connect to the server must go into the "ClientManagement" folder, open the terminal and create a run file using make and after that run the run file so that the user can connect to the server.

There are still some bugs that I need to fix, and there are some other nice features that can be added and improve the project.
