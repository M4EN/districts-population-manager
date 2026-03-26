# Districts Population Manager

**Description:**
A C program to manage districts and their towns' populations. It allows loading data from a file, sorting districts alphabetically and towns by population, adding or deleting districts/towns, calculating total population, and saving the sorted output.

**Features:**

* Load districts and towns from a text file (`districts.txt`).
* Display loaded data.
* Sort districts alphabetically using Radix Sort.
* Sort towns in each district by population.
* Add new districts and towns.
* Delete towns or entire districts.
* Calculate total population, and display max/min town populations.
* Save the sorted data to a file (`sorted_districts.txt`).

**How to Run:**

1. Clone or download this repository.
2. Place your input file `districts.txt` in the same folder.
3. Compile the C code:

```bash
gcc districts.c -o districts
```

4. Run the program:

```bash
./districts
```

5. Follow the on-screen menu options.

**File Structure:**

* `districts.c` : Main program file.
* `districts.txt` : Sample input file with districts and towns.
* `sorted_districts.txt` : Output file created when saving sorted data.

**Notes:**

* Input file format: `DistrictName|TownName|Population` per line.
