#include<functional>
#include <string>
#include <iostream>

template<typename Tparam>
struct Flexible_Default
{
    Tparam value;
    bool is_readin = false;
    Tparam operator()() { return value; }

    void readin(Tparam value)
    {
        is_readin = true;
        this->value = value;
    }
    template<typename Tfunc=std::function<Tparam()>>
    void set(Tfunc condition_in)
    {
        if (!this->is_readin) this->value = condition_in();
    }
};

struct input
{
    Flexible_Default<int> symmetry;
    Flexible_Default<double> mixing_beta;

    /// condition parameters

    /// determine symmetry
    std::string calculation;
    int gamma_only;

    /// determine mixing_beta
    double gap;

    /// fake constructor：assuming all the condition-parameters are read in
    input(std::string calculation, int gamma_only, double gap)
        : calculation(calculation), gamma_only(gamma_only), gap(gap) {};

    /// use a set of lambdas to define the condition
    void set_default_all();

    /// fake readings,  just to show the different reading states.
    /// in practice, there is only one function that reads all the parameters from file
    void read_all(int symmetry, double beta)
    {
        this->symmetry.readin(symmetry);
        this->mixing_beta.readin(beta);
    }
    void read_symmetry(int symmetry)
    {
        this->symmetry.readin(symmetry);
    }
    void read_beta(double beta)
    {
        this->mixing_beta.readin(beta);
    }
    void read_nothing() {}
};

/// use a set of lambdas to define the condition to set each parameters
void input::set_default_all()
{
    auto set_symmetry = [&]() -> int
    {
        if (calculation == "nscf" || calculation == "istate" ||
            calculation == "ienvelope" || gamma_only == true) return 0;
        else return 1;
    };
    this->symmetry.set(set_symmetry);
    
    auto set_mixingbeta = [&]() -> double
    {
        if (gap < 1)return 0.2;
        else return 0.7;
    };
    this->mixing_beta.set(set_mixingbeta);
}
