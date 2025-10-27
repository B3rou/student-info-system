# Student-Info-C-Memory

**Student Information Management System (Memory-Only)** – An interactive C program to manage student profiles in memory. Users can add, update, and view student information, calculate average grades, and see the highest and lowest grades. All data is lost when the program exits.

## Usage

1. Compile the code file:  
   ```bash
   gcc student_system.c -o student_system //Depends to Compiler
   ```
2. Run the program:  
3. Follow the on-screen instructions to add, update, or view student information.

**Note:**  
- Maximum 100 students by default.  
- Names can be up to 29 characters.  
- Grades are floating-point numbers (e.g., 85.5).  
- Data is **not saved** after exiting the program.

# Student-Info-C-File

**Student Information Management System (File-Saving)** – An interactive C program to manage student profiles. Users can add, update, and view student information, calculate average grades, and see the highest and lowest grades. Data is saved to `student_data.csv` and persists between runs.

## Usage

1. Compile the code file:  
   ```bash
   gcc student_system_save.c -o student_system_save //Depends to Compiler
   ```
2. Run the program:  
3. Follow the on-screen instructions to add, update, or view student information.

**Note:**  
- Maximum 100 students by default. // You can rechange it by changing the value of x  
- Names can be up to 29 characters.  
- Grades are floating-point numbers (e.g., 85.5).  
- Data is saved to `student_data.csv` and **will persist** between runs.