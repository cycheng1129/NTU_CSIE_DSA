PROG_LIST = HW4
CASE_LIST = $(shell seq 1 2)
RESULT_LIST := $(foreach X,$(CASE_LIST),result$X.txt)

all: $(RESULT_LIST)
	ls -l $^

CXX = g++
CXXFLAGS = -std=c++11 -O2
$(PROG_LIST): %: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# result1.txt: testing result of input1.txt between HW4 and answer
$(RESULT_LIST): result%.txt: input%.txt HW4
	echo "testcase: $<" > $@
	echo "answer:" >> $@
	cat output$*.answer.txt >> $@
	echo "HW4:" >> $@
	./HW4 < $< > output$*.HW4.txt
	cat output$*.HW4.txt >> $@
	diff output$*.answer.txt output$*.HW4.txt || echo "wrong answer" >> $@

clean:
	rm -f output*.HW4.txt $(PROG_LIST) $(RESULT_LIST)
