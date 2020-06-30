# Production Line Operation, using IPC (Inter-Process Communication)

The fitments move through 4 stages of a production line as shown below.
# Constructor -> Painter -> Controller -> Assembler
In each of these stages, every fitment stays for some time, which can be different, depending on the type of fitment. \
We have 3 types of fitments,hence 3 sections of production line and x(input) products created by each of them.\
The production line schema is shown above:
![alt text](https://github.com/KGArgyropoulos/Production-Line-With-IPC/blob/master/prodLine.png)

To achieve this, we use a model with **semaphores** and **shared memory**.\
More on the implementation techniques and the algorithm used later.

- Compilation: make
- Remove object files: make clean
- Execution: ./simulator x
	* where x is the number of the fitments in each section of the production
- Production line stages
	* Construction: This is the stage where the fitment gets its form(type). This stage works as a general construction driver.
	* Painting: 
	* Control: 
	* Assemblement: 
