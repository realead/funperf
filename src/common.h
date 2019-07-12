#pragma once



#include <timeitmagic.h>


//hide fill implementation from the compiler, so it cannot optimize things away:
void fill(double value, std::vector<double> &array);


//convience for fill array with values
struct Fill{
   std::vector<double> &vec;
   double value;
   Fill(std::vector<double> &vec_, double value_):
          vec(vec_), value(value_)
   {}
   void operator()(){
      fill(value, vec);
   }
};


double MULT_TIME=0.0;


const double MAX_OMEGA=1e20;
const double MIN_OMEGA=1e-20;
const double STEP_FACTOR=1.1;

template<typename Trafo>
void sample_with_timeit(const std::string &fun_name, std::vector<double> &vec){
   for(double omega=MIN_OMEGA; omega<MAX_OMEGA; omega*=STEP_FACTOR){
      double time=timeitmagic::timeit(Trafo(vec), Fill(vec, omega), 100).time/MULT_TIME;
      if(time>1000.0)
          std::cerr<<"bad tan"<<omega<<" "<<time<<" "<<tan(omega)<<"\n";
      std::cout<<fun_name<<","<<omega<<","<<(time)<<"\n";
   } 
}


//it is small enough for L1-cache
const int N=2000;

inline void warm_up(std::vector<double> &vec){
   //repeat it 20 times as warm up:
   MULT_TIME=timeitmagic::timeit([&vec](){for(auto &v:vec) v*=1.1;}, Fill(vec, 1.0),20).time;
   std::cerr<<"Mult time:"<<MULT_TIME<<"\n";
   std::cerr<<"Dep time: "<<timeitmagic::timeit([&vec](){double prod=1.0; for(auto &v:vec) prod*=v; vec[0]=prod;}, Fill(vec, 1.0),20).time<<"\n";
}


