#include <vector>
#include <string>
#include <iostream>
#include <cmath>


#include "common.h"


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


int main(){
 
   std::vector<double> vec(N);
   warm_up(vec);

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

   //hyp functions:
   sample_with_timeit<Transform<&sinh> >("sinh", vec);
   sample_with_timeit<Transform<&cosh> >("cosh", vec);
   sample_with_timeit<Transform<&tanh> >("tanh", vec);

   //a-hyp functions:
   sample_with_timeit<Transform<&asinh> >("asinh", vec);
   sample_with_timeit<Transform<&acosh> >("acosh", vec);
   sample_with_timeit<Transform<&atanh> >("atanh", vec);

   //other functions:
   sample_with_timeit<Transform<&sqrt> >("sqrt", vec);
   sample_with_timeit<Transform<&exp> >("exp", vec);
   sample_with_timeit<Transform<&log> >("log", vec);

   //ensure that the last was not optimized away:
   fill(1.0, vec);
}

