# A Step-by-Step Guide to setting up VidTube
In this guide, we'll walk you through the process of setting up and building VidTube. We'll cover each component, including the TCP server, Node.js server and the front end.

## Prerequisites:
Before you begin, make sure you have the following installed on your machine:

- Node.js: For running the Node.js server.
- Android Studio: For running the mobile app.
- MongoDB: For storing and managing data. Please install MongoDB locally.

## Step 1: Download the Repositories
### Server Repository
Please download the server repository from github (already contains the build for the web app): [server's repository](https://github.com/OCDev1/VidTube-server/tree/main-part4)

### App Repository
Please download the Android app repository from github: [app's repository](https://github.com/eyalg43/project_android/tree/mainPart4)

## Step 2: Build the TCP Server
- Make sure you are in a Linux based environment.
- Please download the TCP server repository from github: [TCP Server repository](https://github.com/maxshabs/vidtube-part4/tree/main)
- Open terminal at the project directory.
- Use the g++ compiler to compile the code. Assuming you have saved your code in a file named server.cpp, run the following command:
```
g++ -std=c++17 -o server server.cpp
```
- Like this:

  ![Screenshot_20](https://github.com/user-attachments/assets/ac42f35f-4bd3-4faa-93e6-7866c1ea86a3)

## Step 3: Initializing the Node.js Server
- Navigate to the directory where you downloaded the Node.js server repository.
- Go to the node.js server folder (VidTube-server)->services->cppCommunication.js and change the following address to the IP address that the TCP server is running on, if you are on a VM enter the VM's IP address:

  ![Screenshot_16](https://github.com/user-attachments/assets/6208414a-8f4b-4192-8450-55d7974ae8db)

- Run the following command to install the required dependencies: `npm install`

  ![Screenshot_21](https://github.com/user-attachments/assets/1cef55c9-923f-4b29-8d7d-6b67a7825327)


## Step 4: Setting up config and .env.local
In the project directory go to the "config" folder (it's in the main project directory) and inside it you will find a file called ".env.local", inside ".env.local" change the connection string to the connection string of your MongoDB, and set PORT to 12345. it should look something like this:

```
CONNECTION_STRING=mongodb://localhost:27017/vidtube (change to the connection string of your MongoDB)`
PORT=12345 (NOTE: you must use 12345 for it to work)
there is also JWT_SECRET=your_secret_key (you can ignore this)
```

## Optional: Database initialization script
Included in the project is a script called "insertData.js" which will initialize the database with users, videos and comments. we highly reccomend you run this script in order to get the best experience and see all the features (and also to save you some time (: )

You can run the script by typing ```node insertData.js``` (make sure mongoDB is running on your computer) wait for the script to finish and your database called "Vidtube" should be initialized with videos, users and comments, hooray!
**NOTE:** do this before running the server

**NOTE:** in order for the DB to be initialized with the users, videos and comments of the script, make sure you don't already have a database called "vidtube" (or else the script won't add it's data), if you do then delete the database and run the script again.
