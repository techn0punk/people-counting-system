# People Counting System (PCS)

> This project was developed as part of the course "Project Computer Systems Engineering" in the [Computer Engineering](https://ce-bachelor.htw-berlin.de/) program at [HTW Berlin](https://www.htw-berlin.de/).

## Abstract:

We are planning to develop a machine that counts the number of people in a room. This can be useful to comply with any regulations on the number of participants at, e.g. in the context of infection control laws.

## Approach:

Our objectives are achieved by placing sensors at the entrance of the room. These sensors can register whether a person enters or leaves the room. The data is collected, stored and processed by a *Raspberry Pi*. The *Pi* also controls the output of the display and the optional light signalling system.

![Diagram](doc/img/diagram.png)

## Installation

Assuming you have cloned this Repo to your Pi and your in the project directory.

```
cd src
make
sudo make install
```

## Demo

[Video in the HTW Mediathek](https://mediathek.htw-berlin.de/video/People-Counting-System-28Demo29-2D-Projekt-Computer-Systems-Engineering/32b1e746ed77554b97dea0341d423c2c)

## [Poster](doc/poster/pcsposter5.pdf)
![Poster](doc/img/poster.jpg)
