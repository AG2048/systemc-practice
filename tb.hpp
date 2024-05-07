#include <systemc.h>

SC_MODULE(tb){
    sc_in<bool>         clk;
    sc_out<bool>        rst;
    sc_out<sc_int<16>>  inp;
    sc_in<sc_int<16>>  outp;

    // Handshake
    sc_out<bool>    inp_vld_sig;
    sc_in<bool>     inp_rdy_sig;
    sc_in<bool>     outp_vld_sig;
    sc_out<bool>    outp_rdy_sig;

    void source(); // leaving the behaviour codes to other files
    void sink();

    SC_CTOR(tb){
        SC_CTHREAD(sink, clk.pos());
        SC_CTHREAD(source, clk.pos());
    }
};