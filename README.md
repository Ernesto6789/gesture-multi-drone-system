# gesture-multi-drone-system
A gesture-controlled, encrypted multi-drone system designed for secure coordination and emergency telepresence

---

## Overview

This project aims to develop a secure and intuitive multi-drone control system primarely using hand gestures and encrypted wireless communication. The goal is to enable reliable emergency telepresence and remote triage, which can provide assistive navigation support in risky areas such as disaster zones and industrial accidents.

By leveraging gesture input and combining it with real-time encrypted coordination, operators woudl be able to remotely command multiple drones to survey, assist, and navigate hazardous environments safely and efficiently with less risk.

---

## Motivation

During emergencies, quick situational awareness and intervention can save lives. However, dangerous environments make it risky for first responders to act directly. Multi-drone systems controlled remotely offer scalable telepresence and assistance capabilities in tehse scemario, but they must be:

- **Intuitive** to control under pressure (gesture-based input)
- **Secure** to prevent interception or misuse (encrypted comms)
- **Coordinated** to perform complex tasks in real time (swarm logic --> Future Implementation)

This project explores how these challenges can be addressed by integrating encrypted wireless protocols, inertial motion sensing, and multi-agent coordination while taking serious consideration human factors, safety, and medical applicability. Making this project especially suited for life-critical environments.

---

## Features

- **AES-128 Encrypted Communication** ensuring secure command and data transfer
- **Gesture Recognition** IMU sensors (MPU6050) integration for natural, hands-free control
- **Multi-Drone System Coordination** to perform synchronized navigation and task execution
- **Optimized for High-Risk Settings** such as disaster areas, industrial facilities, and medical emergency scenarios.

---

## Tech Stack

- **Hardware**: ESP32 microcontrollers, BNO055+BMP280, NRF24L01 wireless modules, MPU6050 IMU sensors
- **Software**: Arduino IDE, Python for encryption and simulation, VSCode
- **Encryption**: AES-128 for secure data transmission
- **Languages**: C++, Python

---

## System Architecture

_System diagram coming soon_  
_Includes gesture input module, encrypted communication layer, and multi-drone coordination engine._

---

## Roadmap

### Phase 1: Research & Setup
- [x] Establish project and repo structure
- [ ] Design system architecture focusing on emergency telepresence needs

### Phase 2: Encrypted Communication
- [ ] Implement secure AES-128 wireless messaging
- [ ] Test reliable comms under simulated interference conditions

### Phase 3: Gesture Input & Mapping
- [ ] Capture and interpret operator gestures for drone control
- [ ] Optimize gesture recognition for fast, accurate commands

### Phase 4: Multi Coordination & Navigation
- [ ] Develop multi-drone command broadcasting and synchronization
- [ ] Implement assistive navigation algorithms for obstacle avoidance and pathfinding in complex environments

### Phase 5: Integration & Demonstration
- [ ] Combine all modules for a functional emergency telepresence drone swarm
- [ ] Document system performance and potential real-world applications

---

## How to Run (WIP)

1. Clone the repo:
   ```bash
   git clone https://github.com/your-username/gesture-drone-swarm.git
