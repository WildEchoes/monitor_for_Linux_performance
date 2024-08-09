# <center> monitor_for_Linux_performance
A project for monitoring system performance across distributed systems, exclusively designed for Linux environments.

## Usage
1. Create Environment

I recommend using Docker to create a consistent and isolated environment for running this project.
I have prepared all the necessary Docker commands for ease of use; you just need to have a basic understanding of Docker.

- Create Image
```bash
cd docker
./docker_image_build.sh
```
- Create Contianer
```bash
cd docker
./docker_contianer_create.sh
```
Now, you have a docker Contianer! You can run this project now.

2. Compilation
- Enter the container
```bash
cd docker
./docker_into.sh
```
- compilation
```bash
cd /work
mkdir build
cd build
cmake ..
make -j8 
```

3. Running
- Run Server  
open a new terminal
```bash
cd bin
./server
```
- Run Monitor  
open a new terminal
```bash
cd bin
./monitor
```
- Run Display  
open a new terminal
```bash
cd bin
./display
```




