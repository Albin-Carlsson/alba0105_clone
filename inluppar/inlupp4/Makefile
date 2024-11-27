TEST_DIR=test
SRC_DIR = src
ORG_DIR = $(SRC_DIR)/org/ioopm/calculator
TEST_DIR = $(ORG_DIR)/test

all:
	javac -d classes -sourcepath src src/org/ioopm/calculator/Calculator.java

run:
    # java -cp classes org.ioopm.calculator.org.ioopm.calculator.Calculator
	java -cp classes org.ioopm.calculator.Calculator

test:
	# javac -cp junit-platform-console-standalone-1.8.1.jar StandardTests.java
	# java -jar junit-platform-console-standalone-1.8.1.jar -cp . -c StandardTests
	# javac -cp junit-platform-console-standalone-1.8.1.jar unitTestsAST.java
	# java -jar junit-platform-console-standalone-1.8.1.jar -cp . -c unitTestsAST
	javac -cp lib/junit-platform-console-standalone-1.8.1.jar -d test -sourcepath src src/org/ioopm/calculator/test/unitTestsAST.java
	java -jar lib/junit-platform-console-standalone-1.8.1.jar -cp ./test --select-class unitTestsAST

test_output:
	java -cp classes org.ioopm.calculator.Calculator < src/org/ioopm/calculator/test/easyInputTest.txt > src/org/ioopm/calculator/test/easyOutputTest.txt

test_diff:
	diff src/org/ioopm/calculator/test/easyOutputTest.txt src/org/ioopm/calculator/test/easyExpectedOutputTest.txt

clean:
	rm -rf classes
	rm -rf test