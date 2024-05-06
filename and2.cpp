#include <systemc.h>

SC_MODULE(and2){
    // sc_in<> has .read()
    // sc_out<> has .write()
    sc_in<sc_uint<1>>   a, b;
    sc_out<sc_uint<1>>  f;
    sc_in<bool> clk; // clock, bool = 1 wire

    //data types:
    //sc_uint<N> = unsigned (N is the bitwidth): sc_uint<3> x; x = 0-7
    //sc_int<N> = signed

    // function with no parameter
    void func(){
        // output to f, a's read value and b's read value
        f.write(a.read() & b.read());
    }

    // constructor, name must be same
    SC_CTOR(and2){
        SC_METHOD(func); // function is gonna run "func" as a "method" thread
        //sensitive << a << b; //sensitive to a or b change
        sensitive << clk.pos(); // rising edge (posedge), or clk.neg()


    }

    // 3 types of threads
    // SC_METHOD()  // trigger once every event, same as @always, good for counters / combs
    // SC_THREAD() // only once at beginning, and ends after they are done. can do while() to keep it running
    // SC_CTHREAD() // clock thread. only run per clock edge. can take more than 1 clock to execute. 
}