#include <systemc.h>

SC_MODULE(tb){
    sc_in<bool>         clk;
    sc_out<bool>        rst;
    sc_out<sc_int<16>>  inp;
    sc_out<sc_int<16>>  outp;

    void source(); // leaving the behaviour codes to other files
    void sink();

    SC_CTOR(tb){
        SC_CTHREAD(sink, clk.pos());
        SC_CTHREAD(source, clk.pos());
    }
};