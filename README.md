# Data Structures

This repository contains custom implementations of fundamental data structures in C++: Deque, HashMap, and Map (using a Red-Black Tree). Each data structure is implemented as a templated version, allowing flexibility and potential modification to meet specific requirements. These implementations can serve as alternatives to the corresponding STL data structures.
Each structure is placed withing a project that allows easy testing of functionalities.

## Features

- **Deque**: A double-ended queue implementation that supports insertion and deletion at both ends efficiently.
- **HashMap**: A custom hash map with support for custom hashing functors.
- **Map (RBTree)**: A map implementation backed by a self-balancing red-black tree for efficient operations.

## Data Structures

### Deque

A custom version of the Deque data structure in C++. This templated version can be used as a substitute for the STL `std::deque` or modified to fit specific needs.

**Features:**
- Efficient insertions and deletions from both ends.
- Dynamic memory management.

### HashMap

A custom implementation of a hash map in C++, providing key-value storage with efficient lookup and insertion operations. It includes a `Hash` template that allows the use of custom hashing functors.

**Features:**
- Supports custom hash functions via a template.
- Collision handling with list chaining
- Dynamic resizing for efficient memory usage.

### Map (Red-Black Tree)

A custom implementation of the `Map` data structure in C++, utilizing a Red-Black Tree for self-balancing. This serves as a substitute for `std::map`.

**Features:**
- Self-balancing tree ensures logarithmic time complexity for search, insertion, and deletion.
- Ordered key-value storage.
- Iterator support.
