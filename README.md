![logo_vidtube](https://github.com/user-attachments/assets/3fcbfc8b-f582-429c-9702-0cd3491752f9)

NOTE: this is part of the VidTube project, for the complete wiki of the whole project, go to the wiki tab.

# The TCP Server:
The server code implements a video recommendation system using C++, which integrates with the rest of the project to upgrade the user experience on VidTube by providing better content recommendations.

# How does it work:
The code processes client requests, tracks user history, and generates video recommendations based on other users' viewing habits. The recommendation algorithm identifies videos that were watched by other users who also viewed the same video as the current user and fills any gaps with random videos from the available list.

# How to run this part:
## Build the TCP Server
- Make sure you are in a Linux based environment.
- Please download the TCP server repository from github: [TCP Server repository](https://github.com/OCDev1/VidTube--TCP-Server)
- Open terminal at the project directory.
- Use the g++ compiler to compile the code. Assuming you have saved your code in a file named server.cpp, run the following command:
```
g++ -std=c++17 -o server server.cpp
```
- Like this:

  ![Screenshot_20](https://github.com/user-attachments/assets/ac42f35f-4bd3-4faa-93e6-7866c1ea86a3)

## Run the TCP Server:
- Make sure you set up the TCP server as specified [here](https://github.com/maxshabs/vidtube-part4/wiki/How-to-setup-VidTube#step-2-build-the-tcp-server)
- Using the command line, navigate to the folder that contains the server file and run the following command:
```
./server
```

![Screenshot_22](https://github.com/user-attachments/assets/45457fb4-9509-4954-809e-de559e8f3579)

That's it, the TCP server is running!
