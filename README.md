# Quine-McCluskey Boolean Simplification Tool

## Project Overview

This project implements the **Quine-McCluskey algorithm** to simplify Boolean functions with up to 10 variables. It provides a comprehensive suite of functionalities for Boolean algebra, including:

- Input validation for Boolean expressions.
- Generation of truth tables and canonical forms (SoP and PoS).
- Identification of prime implicants and essential prime implicants.
- Boolean minimization using a heuristic approach.
- Visualization of Karnaugh Maps and logic circuit diagrams.

The program is designed as a learning and research tool for digital design students and professionals.

---

## Features

### Core Functionalities

1. **Boolean Expression Validation**

   - Ensures input is in valid SoP or PoS form.
   - Detects errors such as unbalanced parentheses, invalid operators, or excessive variables.

2. **Truth Table and Canonical Forms**

   - Outputs a truth table for the input Boolean expression.
   - Generates canonical **Sum of Products (SoP)** and **Product of Sums (PoS)** representations.

3. **Prime Implicants (PIs)**

   - Identifies all prime implicants using systematic grouping and combination.
   - Outputs PIs along with the minterms they cover.

4. **Essential Prime Implicants (EPIs)**

   - Determines EPIs that uniquely cover certain minterms.

5. **Uncovered Minterms**

   - Lists minterms not covered by EPIs.

6. **Minimized Boolean Expression**

   - Produces the minimized Boolean expression using a heuristic selection of implicants.

7. **Karnaugh Maps (K-Maps)**

   - Draws K-Maps for Boolean functions with up to 4 variables.
   - Visualizes implicant coverage in the K-Map.

8. **Logic Circuit Diagram**

   - Generates a logic circuit diagram for the minimized Boolean expression.
   - Uses WaveDrom to visualize the circuit.

---

## Installation and Usage

### Prerequisites

- A C++ compiler (e.g., GCC, Clang).
- A code editor or IDE (e.g., Visual Studio Code, CLion).
- WaveDrom viewer for logic circuit visualization.

### Steps to Run the Program

1. **Clone the Repository**

   ```bash
   git clone https://github.com/FaridaBey/DD1_Proj01.git
   cd <repository_folder>
   ```

2. **Compile the Program**

   ```bash
   g++ -o quine_mccluskey main.cpp
   ```

3. **Run the Program**

   ```bash
   ./quine_mccluskey
   ```

4. **Interact with the Program**

   - Provide a Boolean expression in valid SoP or PoS form.
   - Review outputs such as truth tables, K-Maps, and logic circuits.

---

## Example Input and Outputs

### Sample Input

```
a + b'c + d'(a + b)
```

### Sample Output

- Truth Table
- Canonical SoP: `a'b'c' + ab'c`
- Canonical PoS: `(a + b' + c')(a' + b + c)`
- Prime Implicants: `{a'b'c', ab'c}`
- Essential Prime Implicants: `{ab'c}`
- K-Map and Logic Circuit Diagrams (displayed as images).

---

## Contributions

### Farida Bey

- Truth table generation and canonical forms.
- Prime implicant generation.
- Boolean expression minimization.
- K-Map representation.
- Debugging and issue fixes.

### Hussein Elazhary

- Boolean expression validation.
- Essential prime implicants identification.
- Handling uncovered minterms.
- Logic circuit visualization.
- Debugging and issue fixes.

---

## Test Cases

The program has been tested with a variety of Boolean expressions, including:

1. `(a + b + c)(a + b' + d')`
2. `ab + a'b' + b'c + ab'`
3. `abc + bcde + b'de + efg`
4. `a'b'c'd' + a'bc'd + abcd`
5. Complex SoP and PoS expressions.

---

## License

This project is licensed under the MIT License. See the LICENSE file for details.

