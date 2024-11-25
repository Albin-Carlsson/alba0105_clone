all:
	javac -d classes -sourcepath src src/org/ioopm/calculator/Calculator.java

run:
    # java -cp classes org.ioopm.calculator.org.ioopm.calculator.Calculator
	java -cp classes org.ioopm.calculator.Calculator

test:
	javac -cp junit-platform-console-standalone-1.8.1.jar StandardTests.java
	java -jar junit-platform-console-standalone-1.8.1.jar -cp . -c StandardTests

clean:
	rm -rf classes