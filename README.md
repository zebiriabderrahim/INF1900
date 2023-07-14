
##
                        ██████╗░░█████╗░██████╗░███████╗██╗░░██╗
                        ██╔══██╗██╔══██╗██╔══██╗██╔════╝╚██╗██╔╝
                        ██████╔╝██║░░██║██████╦╝█████╗░░░╚███╔╝░
                        ██╔══██╗██║░░██║██╔══██╗██╔══╝░░░██╔██╗░
                        ██║░░██║╚█████╔╝██████╦╝███████╗██╔╝╚██╗
                        ╚═╝░░╚═╝░╚════╝░╚═════╝░╚══════╝╚═╝░░╚═╝

# ROBEX Project

Welcome to the Autonomous Robot Project! This project involves the development of an autonomous robot equipped with a microcontroller (ATmega324pa). The robot is programmed primarily in C and C++, with the inclusion of assembly language as needed. It leverages principles of microprocessor operation and digital systems to navigate different paths based on information captured by its sensors in its immediate environment.

The project introduces key concepts such as reading and writing on analog and digital ports, PWM comparator control, timer control, and memory addressing. By applying these concepts, the robot achieves precise control and efficient operation. Mathematical problem-solving techniques may also be employed to tackle trajectory calculation and distance measurement challenges.

## Project Overview

The core of the robot's functionality is implemented using C and C++ programming languages, with the possibility of incorporating assembly language when necessary. The codebase utilizes GCC, a comprehensive set of programming tools for Atmel AVR microcontrollers, facilitating efficient and optimized development.

The robot operates in a closed-loop system, continuously reading sensor data to adjust motor speed and direction. This closed-loop control system ensures precise navigation and responsiveness.


## Features

- All classes representing physical functionalities of the robot have been encapsulated within a new class called "Robot". The sensor classes have also been added, all within the library.

- The main function consolidates the entire project and uses a switch case to choose the desired functionality to execute.

- The speeds of each wheel of the robot are recorded on each iteration of the loop (if in forward traversal mode before U-turn). In memory, (255,255) indicates the end instruction of the resumption mode.

## Getting Started

To compile and install the project on the robot, follow these steps:

1. Clone this repository to your local machine.

2. Navigate to the `app` directory.

3. Run the following bash command: `./makelib`. This will execute the bash script that performs the following tasks:
    - `make lib`: Creates the library in the lib directory.
    - `make install`: Installs the app on the robot.

Alternatively, you can run `make install` directly in the app directory to install the app on the robot.

## Usage

Once the app is installed on the robot, you can choose different paths and functionalities by running the compiled program. The switch case in the main function allows you to select the desired functionality to execute based on your requirements.

## Contributing

Contributions to this project are welcome. Feel free to fork the repository, make your changes, and submit a pull request.




