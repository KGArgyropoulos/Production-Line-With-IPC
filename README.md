# Production Line Operation, using IPC (Inter-Process Communication)

The fitment moves through 4 stages of a production lines as shown in the schema.
# Constructor -> Painter -> Controller -> Assembler
In each of these stages, the fitment stays for some time, which is different, depending on the type of fitment. \
We have 3 types of fitments,hence 3 sections of production line and x products created by each of them, where x is the number of the fitments in every section of the production.\
Our purpose is to optimize the production line so that the fitments will be complete, as quickly as they finish each stage of the production.\
To achieve this, we use a model with **semaphores** and **shared memory**.\
More on the implementation techniques later.

- Compilation: make
- Remove object files: make clean
- Execution: ./simulator x
	* where x is the number of the fitments in every section of the production
- Production line stages
	* Construction: This is the stage where the fitment gets its form. This stage works as a general construction driver.
	* Painting: 
	* Control: 
	* Assemblement: 
