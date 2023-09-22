#include "sparseSystem.h"
#include "engine.h"

#include <iostream>
#include <chrono>
using namespace std::chrono;

int main() 
{
    sparseSystem solver;

    std::vector<std::vector<double> > A;
    std::vector<double> b;
    std::vector<double> x;

    std::vector<double> row1;
    std::vector<double> row2;
    std::vector<double> row3;

    row1.push_back(3.0);
    row1.push_back(2.0);
    row1.push_back(-1.0);
    row2.push_back(2.0);
    row2.push_back(-2.0);
    row2.push_back(4.0);

    row3.push_back(-1.0);
    row3.push_back(0.5);
    row3.push_back(-1.0);

    A.push_back(row1);
    A.push_back(row2);
    A.push_back(row3);

    b.push_back(1.0);
    b.push_back(-2.0);
    b.push_back(0.0);
    x.push_back(0.0);
    x.push_back(0.0);

    int ierror = 0.0;
    //solution tolerance
    double sol_tol = 1e-6;
    
    /*
        LU TEST
    */
    solver.solver_method = LU;
    auto start_time = high_resolution_clock::now();
    ierror = solver.solve(A, b);
    auto stop_time = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop_time - start_time);
    std::cout << "LU TIME: " << duration.count() << "ms" << std::endl;
    std::cout << "LU SOL: " << solver.output[0] << " | " << solver.output[1] << " | " << solver.output[2] << std::endl;
    if ((abs(solver.output[0]- 1.0) < sol_tol) && (abs(solver.output[1]+ 2.0) < sol_tol) && (abs(solver.output[1]+ 2.0) < sol_tol)){
        std::cout << "| LU PASS |\n";
    }
    else {
        std::cout << "| LU FAIL |\n";
    }


    /*
        QR TEST
    */
    solver.solver_method = SPARSEQR;
    start_time = high_resolution_clock::now();
    ierror = solver.solve(A, b);
    stop_time = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop_time - start_time);
    std::cout << "QR TIME: " << duration.count() << "ms" << std::endl;
    std::cout << "QR SOL: " << solver.output[0] << " | " << solver.output[1] << " | " << solver.output[2] << std::endl;
    if ((abs(solver.output[0]- 1.0) < sol_tol) && (abs(solver.output[1]+ 2.0) < sol_tol) && (abs(solver.output[1]+ 2.0) < sol_tol)){
        std::cout << "| QR PASS |\n";
    }
    else {
        std::cout << "| QR FAIL |\n";
    }

    return 0;
}