PROG_LIST = HW2
CASE_LIST = $(shell seq 1 2)
RESULT_LIST := $(foreach X,$(CASE_LIST),result$X.txt)

all: $(RESULT_LIST)
	ls -l $^

CXX = g++
CXXFLAGS = -std=c++11 -O2
$(PROG_LIST): %: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# result1.txt: testing result of input1.txt between HW2 and answer
$(RESULT_LIST): result%.txt: input%.txt HW2
	echo "testcase: $<" > $@
	echo "answer:" >> $@
	cat output$*.answer.txt >> $@
	echo "HW2:" >> $@
	./HW2 < $< > output$*.HW2.txt
	cat output$*.HW2.txt >> $@
	diff output$*.answer.txt output$*.HW2.txt || echo "wrong answer" >> $@

clean:
	rm -f output*.HW2.txt tmp*.txt $(PROG_LIST) $(RESULT_LIST)
