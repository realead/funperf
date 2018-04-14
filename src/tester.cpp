#include <vector>
#include <string>
#include <iostream>
#include <cmath>


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


//template for different functions
template<double op(double)>
struct Transform{
    std::vector<double> &vec;
    Transform(std::vector<double> &vec_): vec(vec_){}
    
    void operator()(){
      for(auto &v : vec){
          v=op(v);
      }
   }
};




double MULT_TIME=0.0;


const double MAX_OMEGA=1e20;
const double MIN_OMEGA=1e-20;
const double STEP_FACTOR=1.4;

template<typename Trafo>
void sample_with_timeit(const std::string &fun_name, std::vector<double> &vec){
   for(double omega=MIN_OMEGA; omega<MAX_OMEGA; omega*=STEP_FACTOR){
      double time=timeitmagic::timeit(Trafo(vec), Fill(vec, omega), 100).time;
      std::cout<<fun_name<<","<<omega<<","<<(time/MULT_TIME)<<"\n";
   } 
}


//it is small enough for L1-cache
const int N=2000;


int main(){
 
   std::vector<double> vec(N);

   //repeat it 20 times as warm up:
   MULT_TIME=timeitmagic::timeit([&vec](){for(auto &v:vec) v*=1.1;}, Fill(vec, 1.0),20).time;
   std::cerr<<"Mult time:"<<MULT_TIME<<"\n";
   std::cerr<<"Dep time: "<<timeitmagic::timeit([&vec](){double prod=1.0; for(auto &v:vec) prod*=v; vec[0]=prod;}, Fill(vec, 1.0),20).time<<"\n";

   //header: 
   std::cout<<"fun_name,argument,flops\n";

   //trig functions:
   sample_with_timeit<Transform<&sin> >("sin", vec);
   sample_with_timeit<Transform<&cos> >("cos", vec);
   sample_with_timeit<Transform<&tan> >("tan", vec);

   //a-trig functions:
   sample_with_timeit<Transform<&asin> >("asin", vec);
   sample_with_timeit<Transform<&acos> >("acos", vec);
   sample_with_timeit<Transform<&atan> >("atan", vec);

   //ensure that the last was not optimized away:
   fill(1.0, vec);
}

