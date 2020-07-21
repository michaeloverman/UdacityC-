#include <chrono>
#include <iostream>

int main()
{
    // create array
    const int size = 1000;
    static int x[size][size];

long totaltime = 0L;
for (int reps = 0; reps < 100; reps++) {
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            x[i][j] = i + j;
            // std::cout << &x[j][i] << ": i=" << i << ", j=" << j << std::endl;
        }
    }

    // print execution time to console
    auto t2 = std::chrono::high_resolution_clock::now(); // stop time measurement
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	totaltime += duration;
}
long average = totaltime / 100;
    std::cout << "Execution time: " << average << " microseconds" << std::endl;

    return 0;
}