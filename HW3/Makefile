PROG_LIST = HW3
CASE_LIST = $(shell seq 1 3)
RESULT_LIST := $(foreach X,$(CASE_LIST),result$X.txt)

all: $(RESULT_LIST)
	ls -l $^

CXX = g++
CXXFLAGS = -std=c++11 -O2
$(PROG_LIST): %: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# result1.txt: testing result of input1.txt between HW3 and answer
$(RESULT_LIST): result%.txt: input%.txt HW3
	echo "testcase: $<" > $@
	echo "answer:" >> $@
	cat output$*.answer.txt >> $@
	echo "HW3:" >> $@
	./HW3 < $< > output$*.HW3.txt
	cat output$*.HW3.txt >> $@
	diff output$*.answer.txt output$*.HW3.txt || echo "wrong answer" >> $@

clean:
	rm -f output*.HW3.txt $(PROG_LIST) $(RESULT_LIST)
