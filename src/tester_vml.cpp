#include <vector>
#include <string>
#include <iostream>
#include <cmath>

#include <mkl.h>


#include "common.h"


//template for different functions
template<void op(MKL_INT n, const double *x, double *y)>
struct Transform{
    std::vector<double> &vec;
    Transform(std::vector<double> &vec_): vec(vec_){}
    
    void operator()(){
      op(static_cast<MKL_INT>(vec.size()), &vec.at(0), &vec.at(0));
   }
};



int main(){
 
   std::vector<double> vec(N);
   
   warm_up(vec);

   //header: 
   std::cout<<"fun_name,argument,flops\n";

   //trig functions:
   sample_with_timeit<Transform<&vdSin> >("sin", vec);
   sample_with_timeit<Transform<&vdCos> >("cos", vec);
   sample_with_timeit<Transform<&vdTan> >("tan", vec);

   //a-trig functions:
   sample_with_timeit<Transform<&vdAsin> >("asin", vec);
   sample_with_timeit<Transform<&vdAcos> >("acos", vec);
   sample_with_timeit<Transform<&vdAtan> >("atan", vec);

   //hyp functions:
   sample_with_timeit<Transform<&vdSinh> >("sinh", vec);
   sample_with_timeit<Transform<&vdCosh> >("cosh", vec);
   sample_with_timeit<Transform<&vdTanh> >("tanh", vec);

   //a-hyp functions:
   sample_with_timeit<Transform<&vdAsinh> >("asinh", vec);
   sample_with_timeit<Transform<&vdAcosh> >("acosh", vec);
   sample_with_timeit<Transform<&vdAtanh> >("atanh", vec);

   //other functions:
   sample_with_timeit<Transform<&vdSqrt> >("sqrt", vec);
   sample_with_timeit<Transform<&vdLn> >("log", vec);
   sample_with_timeit<Transform<&vdExp> >("exp", vec);



   unsigned int current = vmlGetMode();
   std::cerr<<"current mode: "<<current<<std::endl;
   vmlSetMode(((current | 3)^ 3) | VML_HA);
   sample_with_timeit<Transform<&vdAsinh> >("asinh_ha", vec);

   current = vmlGetMode();
   std::cerr<<"current mode: "<<current<<std::endl;
   vmlSetMode(((current | 3)^ 3) | VML_LA);
   sample_with_timeit<Transform<&vdAsinh> >("asinh_la", vec);


   current = vmlGetMode();
   std::cerr<<"current mode: "<<current<<std::endl;
   vmlSetMode(((current | 3)^ 3) | VML_EP | VML_ERRMODE_IGNORE);
   sample_with_timeit<Transform<&vdAsinh> >("asinh_ep", vec);

   //ensure that the last was not optimized away:
   fill(1.0, vec);
}

