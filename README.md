# Arduino_Bot

This was done for the lab section of ECE 110 at Duke University, it was done for the Integrated Design Challenge (IDC). The IDC tested the creation and functionality of a robot to complete specific tasks and communicate with other bots conducting similar tasks, as well as the team’s capabilities to construct and coordinate.

During the Integrated Design Challenge, teams were split into groups to demonstrate individual bot task completion, as well as communication between bots. The team’s goal is to complete different tasks in order to determine next year’s IDC Challenge. It takes place on a board that is 8 feet x 6 feet containing a map of the world, on which many tasks must be completed by individual robots. The tasks are inspired by challenges that the US National Science Foundation has deemed important to how people live. Each robot will perform its own tasks on its own continent after circling it once by following a black line to a hash mark, and it will display a 1 or 0 depending on the state of the Grand Challenge. The tasks each required the use of a unique sensor. 
In particular, the 4th Grand Challenge, “Prevent Nuclear Terror,”  test required a Hall-Effect Sensor for magnetic field testing. The bot was designed to detect whether a magnetic field was present, and display a 1 if there is a field, and a 0 if it determines there is no magnetic field present. The bot then communicates with the other bots via an XBee module and depending on what signals are received from the other bots, it will add up how many other bots read a 1 and use the resulting sum to display the next Grand Challenge.
	The bot was operated using an Arduino microcontroller that had a BOE shield connected to it. The Arduino was attached to a large metal frame that housed the overall bot, including the servos and sensors. All circuits were connected through the Arduino for all sensors and servos and operated by uploading code to it. 
	Throughout the course of the IDC experience, the overall goals were not only to successfully complete each task and communicate with the other bots but also to learn the engineering process from an electrical engineering perspective. The real-world applications of the bot designed for magnetic field sensing can be applied whenever the presence of a magnetic field is of concern but is limited in detecting magnetic field strength, such as proximity detection or speed reading. 

## Bot SetUp
![](https://github.com/Leo-Gut28/Arduino_Bot/blob/main/Bot_SetUp.png)

## Diagrams 

### RGB Sensor
![](https://github.com/Leo-Gut28/Arduino_Bot/blob/main/RGB-Sensor_Diagram.png)

### Hall Effect Sensor
![](https://github.com/Leo-Gut28/Arduino_Bot/blob/main/Hall-Effect_Diagram.png)

### I2C Display
![](https://github.com/Leo-Gut28/Arduino_Bot/blob/main/Display_Diagram.png)
