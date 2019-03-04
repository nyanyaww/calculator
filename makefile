cc = g++
prom = test
deps = $(shell find ./ -name "*.h")
src = $(shell find ./ -name "*.cpp")
obj = $(src:%.cpp=%.o) 

$(prom): $(obj)
	$(cc) -o $(prom) $(obj)

%.o: %.c $(deps)
	$(cc) -c $< -o $@
clean_o:
	rm -f $(obj)
clean:
	rm -rf $(obj) $(prom)
