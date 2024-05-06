#include <systemc.h>

SC_MODULE(and2){
    // sc_in<> has .read()
    // sc_out<> has .write()
    sc_in<DT>   a;
    sc_in<DT>   b;
    sc_out<DT>  f;
    sc_in<bool> clk; // clock, bool = 1 wire

    // function with no parameter
    void func(){
        // output to f, a's read value and b's read value
        f.write(a.read() & b.read());
    }

    // constructor, name must be same
    SC_CTOR(and2){
        SC_METHOD(func); // function is gonna run "func"
        sensitive << clk.pos(); // rising edge (posedge), or clk.neg()


    }

    // 3 types of threads
    // SC_METHOD()  // trigger once every event, same as @always, good for counters / combs
    // SC_THREAD() // only once at beginning, and ends after they are done. can do while() to keep it running
    // SC_CTHREAD() // clock thread. only run per clock edge. can take more than 1 clock to execute. 
}