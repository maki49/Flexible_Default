#include "flexible_default.hpp"
int main()
{
    input in_1("nscf"/*calculation*/, 0/*gamma_only*/, 0.8/*gap*/);
    in_1.read_nothing();    //symmetry: not read; mixing_beta: not read
    in_1.set_default_all(); //symmetry=0, mixing_beta=0.2
    std::cout << "result of input set 1: " << std::endl;
    std::cout<< "symmetry=" << in_1.symmetry() << ", mixing_beta=" << in_1.mixing_beta() << std::endl;

    input in_2("scf"/*calculation*/, 1/*gamma_only*/, 1.5/*gap*/);
    in_2.read_symmetry(static_cast<int>(1)/*symmetry*/);    //symmetry: read; mixing_beta: not read
    in_2.set_default_all(); //symmetry=1, mixing_beta=0.7
    std::cout << "result of input set 2: " << std::endl;
    std::cout<< "symmetry=" << in_2.symmetry() << ", mixing_beta=" << in_2.mixing_beta() << std::endl;

    input in_3( "scf"/*calculation*/, 0/*gamma_only*/, 1.5/*gap*/);
    in_3.read_beta(static_cast<double>(0.4)/*mixing_beta*/);    //symmetry: not read; mixing_beta: read
    in_3.set_default_all(); //symmetry=1, mixing_beta=0.4
    std::cout << "result of input set 3: " << std::endl;
    std::cout<< "symmetry=" << in_3.symmetry() << ", mixing_beta=" << in_3.mixing_beta() << std::endl;

    return 0;
}
