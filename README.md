# SimulationPlayground

[![ci](https://github.com/cmdc0de/SimulationPlayground/actions/workflows/ci.yml/badge.svg)](https://github.com/cmdc0de/SimulationPlayground/actions/workflows/ci.yml)
[![codecov](https://codecov.io/gh/cmdc0de/SimulationPlayground/branch/main/graph/badge.svg)](https://codecov.io/gh/cmdc0de/SimulationPlayground)
[![CodeQL](https://github.com/cmdc0de/SimulationPlayground/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/cmdc0de/SimulationPlayground/actions/workflows/codeql-analysis.yml)

## About SimulationPlayground
3d Similuation playground 

### Goals:
* This will be a learning project
  * to learn RL ML
  * To test different Reinforced learning (RL) technologies
* 3D environment via standard 3d file formats
  * Rendering engine will use Vulkan
* Uses Reinforced learning (RL) for agent movement and behaviors
  * RL is via an interface that allows easy switching between RL technologies (xgboost, tensorflow, etc)
* Use a physic engine for realizstic movement and collision detection
* agent behavior can be written in c++ or WASM
* Metrics a akin to java's open telemetery
* Task based threading model
* Use c++ 20
  * c++ 20 to take advantage of concurrencies models

### Strech Goals:
* Authoriative server archiecture to allow multiple clients to interact with the Simulation Play ground
  * Describe network communication in a language agnostic format (eg: protobufs or the akin) to allow clients to be created in any langage

## More Details

 * [Dependency Setup](README_dependencies.md)
 * [Building Details](README_building.md)
 * [Troubleshooting](README_troubleshooting.md)
 * [Docker](README_docker.md)
