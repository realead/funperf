
RESULT="../report/test_results.txt"


cd src
g++ tester.cpp filler.cpp -O3 -std=c++11 -I../timeitcpp/include -o tester
./tester > $RESULT


python report_to_images.py $RESULT
