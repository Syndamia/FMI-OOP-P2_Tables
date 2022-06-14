# FMI Tables {#mainpage}

\author Kamen Mladenov; FMI Computer Science, Year 1, Group 6; Project 2, Topic 7
\date 14 June 2022
\copyright GNU General Public License v3.0

<dl>
	<dt>Source Code</dt>
	<dd>https://github.com/Syndamia/FMI-OOP-P2_Tables</dd>
</dl>

## About

"FMI Tables" is a simple implementation of parsing and editing a CSV-style table file, that stores strings, formulas and numbers.

## Structure overview

The project is roughly divided into 3 main components: User Interface, Models and Generic \ref fig1.
- The User Interface is the messenger between a user and the underlying application. All input and output is handled here.
- Models are the general classes that are used in the user interface and that do the value parsing.
- Generic is a place for all code that is can be used independently from the project. Stuff like Pair, String or List.

## Building the project

Instructions are all for `gcc`. All commands should be executed while in the `src` folder.

### Linux/BSD/MacOS

```bash
g++ **/**.cpp -o TicketSystem.out && ./TicketSystem.out
```

### Windows (PowerShell)

```bash
g++ (Get-ChildItem -Recurse *.cpp) -o TicketSystem.exe && ./TicketSystem.exe
```

## Figures

\anchor fig1
**Figure 1:** Overview of the "FMI Ticket System" design

\image html "FMI-OOP-P2_Table Overview.svg" ""
\image latex "FMI-OOP-P2_Table Overview.svg" "Not available in LaTeX!"
