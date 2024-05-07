#include <systemc.h>
#include <fir.hpp>
#include <tb.hpp>

SC_MODULE(SYSTEM){
    // Module declarations
    tb      *tb0; // module_name    variable_name_pointer
    fir     *fir0;

    // Defining signals
    sc_signal<sc_int<16>>   inp_sig;
    sc_signal<sc_int<16>>   outp_sig;
    sc_signal<bool>         rst_sig;
    // Handshake
    sc_signal<bool>         inp_sig_vld;
    sc_signal<bool>         inp_sig_rdy;
    sc_signal<bool>         outp_sig_vld;
    sc_signal<bool>         outp_sig_rdy;
    
    // Defining a clock signal (I'm assuming it's a special class)
    sc_clock clk_sig;

    // Constructor
    SC_CTOR(SYSTEM) 
        : clk_sig("clk_sig", 10, SC_NS){ // construct clock signal -- naming it "clk_sig", 10 ns period, in NS unit
        // Module instance signal connections
        tb0 = new tb("tb0"); // defining tb0 as a new tb called "tb0"
        tb0->clk(clk_sig); // tb0 is a pointer, we find its clk element and assign it clk_sig
        tb0->rst(rst_sig);
        tb0->inp(inp_sig);
        tb0->outp(outp_sig);
        // Handshake
        tb0->inp_vld(inp_sig_vld);
        tb0->inp_rdy(inp_sig_rdy);
        tb0->outp_vld(outp_sig_vld);
        tb0->outp_rdy(outp_sig_rdy);

        fir0 = new fir("fir0"); // defining fir0 as a new fir called fir0
        fir0->clk(clk_sig);
        fir0->rst(rst_sig);
        fir0->inp(inp_sig);
        fir0->outp(outp_sig);
    }
    // Destructor
    ~SYSTEM(){
        delete tb0;
        delete fir0;
    }
};

// Main code:
SYSTEM *top = nullptr;

int sc_main(int argc, char* argv[]){
    top = new SYSTEM("top"); // Define new top module
    sc_start(); // run, start a simulation
    return 0;
}