# check that mkl is set:

if [ -z "$MKL_INCLUDE" ]
then
   echo "MKL_INCLUDE is not set"
   exit 1
fi

if [ -z "$MKL_LIB" ]
then
   echo "MKL_LIB is not set"
   exit 1
fi

## now run:

set -e

mkdir -p "report"

RESULT="../report/test_vml_results.txt"



cd src
# -lmkl_sequential
# -lmkl_gnu_thread -liomp5
g++ tester_vml.cpp filler.cpp -O3 -std=c++11 -I../timeitcpp/include  -I"$MKL_INCLUDE" -Wl,-rpath="$MKL_LIB" -L"$MKL_LIB" -Wl,--no-as-needed -lmkl_intel_ilp64 -lmkl_core -lmkl_sequential -o tester_vml

./tester_vml > $RESULT


python report_to_images.py $RESULT
