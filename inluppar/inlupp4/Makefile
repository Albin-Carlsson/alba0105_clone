JAVA_SOURCE_DIR = src/org
JAVA_TEST_DIR = src/org/ioopm/calculator/test
TARGET_DIR = classes
TEST_TARGET_DIR = classes
LIB_DIR = lib
JUNIT_JAR = $(LIB_DIR)/junit-platform-console-standalone-1.8.1.jar
all:
	javac -d classes -sourcepath src src/org/ioopm/calculator/Calculator.java


run: all
    # java -cp classes org.ioopm.calculator.org.ioopm.calculator.Calculator
	java -cp classes org.ioopm.calculator.Calculator

test:
	javac -cp lib/junit-platform-console-standalone-1.8.1.jar -d classes -sourcepath src src/org/ioopm/calculator/test/AstTest.java
	javac -cp lib/junit-platform-console-standalone-1.8.1.jar -d classes -sourcepath src src/org/ioopm/calculator/test/ParserTests.java
	javac -cp lib/junit-platform-console-standalone-1.8.1.jar -d classes -sourcepath src src/org/ioopm/calculator/test/integrationTests.java
	java -jar $(JUNIT_JAR) -cp $(TEST_TARGET_DIR):$(TARGET_DIR) --scan-class-path

test_output: all
	java -cp classes org.ioopm.calculator.Calculator < src/org/ioopm/calculator/test/InputTests/easyInputTest.txt > src/org/ioopm/calculator/test/InputTests/easyOutputTest.txt
	java -cp classes org.ioopm.calculator.Calculator < src/org/ioopm/calculator/test/InputTests/wrongInputTest.txt > src/org/ioopm/calculator/test/InputTests/wrongOutputTest.txt
	java -cp classes org.ioopm.calculator.Calculator < src/org/ioopm/calculator/test/InputTests/complexInputTest.txt > src/org/ioopm/calculator/test/InputTests/complexOutputTest.txt
	diff src/org/ioopm/calculator/test/InputTests/easyOutputTest.txt src/org/ioopm/calculator/test/InputTests/easyExpectedOutputTest.txt
	diff src/org/ioopm/calculator/test/InputTests/wrongOutputTest.txt src/org/ioopm/calculator/test/InputTests/wrongExpectedOutput.txt
	diff src/org/ioopm/calculator/test/InputTests/complexOutputTest.txt src/org/ioopm/calculator/test/InputTests/complexExpectedOutputTest.txt


clean:
	rm -rf classes
	rm -rf test

