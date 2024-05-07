#include <systemc.h>

SC_MODULE(fir){
    sc_in<bool>         clk;
    sc_in<bool>         rst;
    sc_in<sc_int<16>>   inp;
    sc_out<sc_int<16>>  outp;

    // Handshake
    sc_in<bool>    inp_vld_sig;
    sc_out<bool>     inp_rdy_sig;
    sc_out<bool>     outp_vld_sig;
    sc_in<bool>    outp_rdy_sig;

    void fir_main(); // leaving the behaviour codes to other files

    SC_CTOR(fir){
        SC_CTHREAD(fir_main, clk.pos()); // SC_CTHREAD runs fir_main when the clk sensitive edge occurs
        reset_signal_is(rst, true); // Reset is asserted high, false will mean reset asserted low. This resets SC_CTHREAD
    }
};