all: 
	make --directory=Day1/1
	make --directory=Day1/2
	make --directory=Day2/1
	make --directory=Day2/2
	make --directory=Day3/1
	make --directory=Day3/2
	make --directory=Day4/1	
clean:
	make clean --directory=Day1/1
	make clean --directory=Day1/2
	make clean --directory=Day2/1
	make clean --directory=Day2/2
	make clean --directory=Day3/1
	make clean --directory=Day3/2
	make clean --directory=Day4/1	

