# Flocking [![Build Status](https://travis-ci.org/gagbo/Flocking.svg?branch=master)](https://travis-ci.org/gagbo/Flocking)

Implementation of Emergence through flocking autonomous agents in C++.
This little project is inspired by
[Tech.io nice
tutorial](https://tech.io/playgrounds/1003/flocking-autonomous-agents/)
on the subject, and aims to make me play with graphical components/libraries
in C++.

## Dependencies

The application (compilation and execution) has only been tested with :
- CMake 3.8 (to use directly Qt5::Widgets in target\_link\_libraries)
- Qt 5.9.2
- GCC 7.2.1

It might work with other versions, but it is not guaranteed.

## TODOs
- [x] Wrap-around for the ants
- [ ] Create a Menu bar to control the simulation
    - [x] Put placeholder items in the menubar
    - [ ] Add new ants
    - [ ] Kill a random ant ( or an ant with a low "score" )
    - [ ] Stop the simulation
    - [ ] Step the simulation
    - [ ] Play the simulation
- [ ] Implement decision strategies
    - [x] add some decisions strategies...
    - [ ] ...and add some sliders in a dock widget to control their weights in runtime
- [ ] Proper drawing for ants
