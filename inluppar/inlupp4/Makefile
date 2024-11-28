JAVA_SOURCE_DIR = src/org
JAVA_TEST_DIR = src/org/ioopm/calculator/test
TARGET_DIR = classes
TEST_TARGET_DIR = classes
LIB_DIR = lib
JUNIT_JAR = $(LIB_DIR)/junit-platform-console-standalone-1.8.1.jar
all:
	javac -d classes -sourcepath src src/org/ioopm/calculator/Calculator.java

compile:
run:
    # java -cp classes org.ioopm.calculator.org.ioopm.calculator.Calculator
	java -cp classes org.ioopm.calculator.Calculator

test:
	javac -cp lib/junit-platform-console-standalone-1.8.1.jar -d classes -sourcepath src src/org/ioopm/calculator/test/AstTest.java
	javac -cp lib/junit-platform-console-standalone-1.8.1.jar -d classes -sourcepath src src/org/ioopm/calculator/test/ParserTests.java
	javac -cp lib/junit-platform-console-standalone-1.8.1.jar -d classes -sourcepath src src/org/ioopm/calculator/test/integrationTests.java
	java -jar $(JUNIT_JAR) -cp $(TEST_TARGET_DIR):$(TARGET_DIR) --scan-class-path

test_output:
	java -cp classes org.ioopm.calculator.Calculator < src/org/ioopm/calculator/test/easyInputTest.txt > src/org/ioopm/calculator/test/easyOutputTest.txt

test_diff:
	diff src/org/ioopm/calculator/test/easyOutputTest.txt src/org/ioopm/calculator/test/easyExpectedOutputTest.txt

clean:
	rm -rf classes
	rm -rf test



# Maven
#MVN = mvn
#
#all: compile
#
#compile:
#	mkdir -p $(TARGET_DIR)
#	javac -d $(TARGET_DIR) -sourcepath $(JAVA_SOURCE_DIR) $(JAVA_SOURCE_DIR)/org/ioopm/calculator/**/*.java
#	javac -d $(TARGET_DIR) -sourcepath $(JAVA_SOURCE_DIR) $(JAVA_SOURCE_DIR)/org/ioopm/calculator/Calculator.java
#
#
#test-compile:
#	mkdir -p $(TEST_TARGET_DIR)
#	javac -d $(TEST_TARGET_DIR) -sourcepath $(JAVA_SOURCE_DIR):$(JAVA_TEST_DIR) -cp $(JUNIT_JAR):$(TARGET_DIR) $(JAVA_TEST_DIR)/org/ioopm/calculator/**/*.java
#
#run: compile
#	java -cp $(TARGET_DIR) org.ioopm.calculator.Calculator
#
#test: test-compile
#	java -jar $(JUNIT_JAR) --class-path $(TEST_TARGET_DIR):$(TARGET_DIR) --scan-class-path
#
#clean:
#	rm -rf $(TARGET_DIR)
#	rm -rf $(TEST_TARGET_DIR)
#
#maven:
#	$(MVN) clean install