# People Counting System (PCS)

## Abstract:

We are planning to develop a machine that counts the number of people in a room. This can be useful to comply with any regulations on the number of participants at, e.g. in the context of infection control laws.

## Objectives:

- Accurate detection of people passing through a door (one by one).
- Differentiation between two directions of movement: *going in* and *going out*
- Keeping a constantly updated count of people in a room
- Showing the counter value on a display
- Possibility to set a participant limit, with continous comparison between the limit and the current count
- Displaying a warning (either on the display or with a light signal), in case of:
  - approaching the limit
  - reaching the limit
  - exceeding the limit

## Approach:

Our objectives are achieved by placing sensors at the entrance of the room. These sensors can register whether a person enters or leaves the room. The data is collected, stored and processed by a *Raspberry Pi*. The *Pi* also controls the output of the display and the optional light signalling system.

![Diagram](doc/img/diagram.png)
