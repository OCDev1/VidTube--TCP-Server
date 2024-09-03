# A Step-by-Step Guide to setting up VidTube
In this guide, we'll walk you through the process of setting up and building VidTube. We'll cover each component, including the TCP server, Node.js server and the front end.

## Prerequisites
- Make sure you set up VidTube by following the instructions [here](https://github.com/maxshabs/vidtube-part4/wiki/How-to-setup-VidTube)

## Step 1: Run the TCP Server
- Make sure you set up the TCP server as specified [here](https://github.com/maxshabs/vidtube-part4/wiki/How-to-setup-VidTube#step-2-build-the-tcp-server)
- Using the command line, navigate to the folder that contains the server file and run the following command:
```
./server
```

![Screenshot_22](https://github.com/user-attachments/assets/45457fb4-9509-4954-809e-de559e8f3579)

## Step 2: Run the Node.js Server
- Open a new terminal or command prompt window.
- Navigate to the directory where your Node.js server code is located.
- Install the required dependencies with (if you haven't already): `npm install`.

Start the Node.js server with: `npm start`.

![Screenshot_24](https://github.com/user-attachments/assets/8d889797-5762-4b95-a0b3-5629142a8e70)

## Step 3: Run the VidTube App in Android Studio
- Open Android Studio.
- Select "Open an existing Android Studio project" and navigate to the directory where you downloaded the VidTube app repository.
- Once the project is loaded, click on the "Run" button (green play icon) located at the top of Android Studio.
- Choose an emulator or connect your Android device to run the VidTube app.

## Step 4: Make sure everything is Running
- TCP Server: Command line should look like this:

  ![Screenshot_25](https://github.com/user-attachments/assets/da828f70-7849-4536-bd98-797a6c8210a6)

- Node.js Server (and Web app): Open a web browser and navigate to  http://localhost:12345 , You should see the VidTube homepage.

- VidTube App: Once the app is successfully launched from Android Studio, you should be able to interact with it on the emulator.
