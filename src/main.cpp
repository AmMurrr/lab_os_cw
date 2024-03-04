#include <iostream>
#include <fstream>
#include <vector>
#include "potalloc.hpp"
#include "frblalloc.hpp"
#include <chrono>

int main(int argc, char const *argv[])
{
    size_t start_i = 0;
    size_t end_i = 100;
    frbl frbl_allocator;
    pot pot_allocator;

    std::vector<char*> pot_alloc;
    std::vector<double> coordinates_frbl;
    std::vector<double> coordinates_pot;


    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i=start_i; i < end_i; i++){
        void* p = frbl_allocator.fmalloc(i);
        auto current_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = current_end - start;
        coordinates_frbl.push_back(duration.count());
        frbl_allocator.ffree(p, i);

   }

    

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Время выполнения free_block_allocator " << duration.count() << " секунд" << std::endl;
    
    char ans;
    std::cout << "Продолжим со 2м аллокатором?(y/n)";
    std::cin >> ans;
    if(ans == 'n') return 0;

    auto start1 = std::chrono::high_resolution_clock::now();

    for (int i=0; i < end_i - start_i; i++){   
        pot_alloc.push_back(pot_allocator.malloc(32));
        auto current_end1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = current_end1 - start1;
        coordinates_pot.push_back(duration.count());


    }
    for (int i=0; i < end_i - start_i; i++){   
        pot_allocator.free(pot_alloc[i]);
    }

    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration1 = end1 - start1;
    std::cout << "Время выполнения power_of_two_allocator " << duration1.count() << " секунд" << std::endl;


    for (int i = start_i; i < end_i; i++) {
        std::cout << i << " " << coordinates_pot[i - start_i] << "   " << coordinates_frbl[i - start_i]<< std::endl;
    }
        
    
    return 0;
}
